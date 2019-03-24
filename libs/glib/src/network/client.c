/*
** ETNA PROJECT, 05/02/2019 by martin_h, hamide_a, despla_g, weber_w
** resLib
** File description:
**      Wrapper around the socket API.
*/

#include <string.h>

#include "network/packer.h"
#include "network/client.h"

static void TClient_Init(TClient *this);
static int TClient_Receving(void *p_args);

static SDL_mutex *mutex_message_event = NULL;

TClient *New_TClient(void)
{
    TClient *this = malloc(sizeof(TClient));

    if(!this) return NULL;
    TClient_Init(this);
    this->Free = TClient_New_Free;
    return this;
}

static void TClient_Init(TClient *this)
{
    this->Connect = TClient_Connect;
    this->Send = TClient_Send;
    this->Recv = TClient_Recv;
    this->Start_Recv = TClient_Start_Recv;
    this->Stop_Recv = TClient_Stop_Recv;
    this->Disconnect = TClient_Disconnect;

    this->On_Message = NULL;
    this->Server_On_Message = NULL;
    this->On_Disconnect = NULL;
    this->Server_On_Disconnect = NULL;

    this->sock = -1;
    this->is_receving = 0;
    this->server = NULL;
    this->client_thread = NULL;
    if (!mutex_message_event)
        mutex_message_event = SDL_CreateMutex();
}

int TClient_Connect(TClient *this, const char *addr, unsigned short int port)
{
    if (this->sock != -1)
        return (-1);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN sin = { 0 };
    struct hostent *hostinfo;

    if(sock == INVALID_SOCKET)
        return (-1);

    hostinfo = gethostbyname(addr);
    if (hostinfo == NULL)
        return (-1);

    sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
    sin.sin_port = htons(port);
    sin.sin_family = AF_INET;

    if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
        return (-1);

    SocketNonBlocking(sock, 0);
    this->sock = sock;
    return (0);
}

int TClient_Send(TClient *this, TMessage message)
{
    if (this->sock == -1)
        return (-1);

    unsigned char *buffer = malloc(sizeof(unsigned char) * (message.len + 2));
    unsigned char *start_buffer = buffer;
    memset(buffer, '\0', message.len + 2);
    int total = 0;
    int bytesleft = (message.len + 2);
    int n;

    buffer = pack_int(buffer, message.len);
    memcpy(buffer, message.message, message.len);

    while(total < message.len) {
        n = send(this->sock, start_buffer + total, bytesleft, 0);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
    }

    free(start_buffer);
    return (n == -1 ? -1 : 0);
}

int TClient_Recv(TClient *this, TMessage *message)
{
    if (this->sock == -1)
        return (-1);

    unsigned char buffer_len[2];
    int recv_res = recv(this->sock, buffer_len, 2, 0);
    message->len = recv_res;
    #ifdef _WIN32
    if (recv_res <= 0) return (WSAGetLastError());
    #else
    if (recv_res <= 0) return (errno);
    #endif

    unpack_int(buffer_len, &(message->len));

    unsigned char *buffer = malloc(sizeof(unsigned char) * message->len);
    message->len = recv(this->sock, buffer, message->len, 0);

    message->message = buffer;

    return (message->len);
}

void TClient_Start_Recv(TClient *this, TServer *server)
{
    if (this->is_receving == 0) {
        if (server)
            this->server = server;
        this->is_receving = 1;
        this->client_thread = SDL_CreateThread(TClient_Receving, "TClient_Receving", (void*)this);
    }
}

void TClient_Stop_Recv(TClient *this)
{
    if (this->is_receving == 1) {
        this->is_receving = 0;
        SDL_WaitThread(this->client_thread, NULL);
    }
}

static int TClient_Receving(void *p_args)
{
    TClient *client = (TClient*)p_args;

    while (client && client->is_receving) {
        TMessage message;
        int res_read = TClient_Recv(client, &message);
        #ifdef _WIN32
        if (res_read != WSAEWOULDBLOCK && res_read != EAGAIN && message.len > 0)
        #else
        if (res_read != EWOULDBLOCK && res_read != EAGAIN && message.len > 0)
        #endif
            {
            SDL_LockMutex(mutex_message_event);
            if (client->On_Message)
                client->On_Message(client, message);
            else if (client->Server_On_Message && client->server)
                client->Server_On_Message(client, client->server, message);
            SDL_UnlockMutex(mutex_message_event);
        }
        else if (message.len == 0) {
            client->is_receving = 0;
        }
    }

    SDL_LockMutex(mutex_message_event);
    if (client->On_Disconnect)
        client->On_Disconnect(client);
    if (client->Server_On_Disconnect && client->server)
        client->Server_On_Disconnect(client, client->server);
    SDL_UnlockMutex(mutex_message_event);
    closesocket(client->sock);
    client->server = NULL;
    client->Free(client);
    return (0);
}

void TClient_Disconnect(TClient *this)
{
    if (this->sock != -1) {
        this->Stop_Recv(this);
        closesocket(this->sock);
    }
}

void TClient_New_Free(TClient *this)
{
    free(this);
}

/*
** ETNA PROJECT, 05/02/2019 by martin_h, hamide_a, despla_g, weber_w
** resLib
** File description:
**      Wrapper around the socket API.
*/

#include <string.h>

#include "packer.h"
#include "client.h"

static void TClient_Init(TClient *this);
static int TClient_Recv(TClient *this, TMessage *message);
static void *TClient_Receving(void *p_args);

static pthread_mutex_t mutex_message_event = PTHREAD_MUTEX_INITIALIZER;

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

    this->sock = sock;
    return (0);
}

int TClient_Send(TClient *this, TMessage message)
{
    if (this->sock == -1)
        return (0);

    char *buffer = malloc(sizeof(char) * (message.len + 2)); // size of message + message
    char *start_buffer = buffer;
    memset(buffer, '\0', message.len + 2);
    int total = 0;
    int bytesleft = (message.len + 2);
    int n;

    buffer = pack_int(buffer, message.len);
    strcat(buffer, message.message);

    while(total < message.len) {
        n = send(this->sock, start_buffer + total, bytesleft, 0);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
    }

    free(start_buffer);
    return (n == -1 ? -1 : 0);
}

static int TClient_Recv(TClient *this, TMessage *message)
{
    if (this->sock == -1)
        return (0);

    char buffer_len[2];
    int recv_res = recv(this->sock, buffer_len, 2, MSG_DONTWAIT);
    message->len = recv_res;
    if (recv_res <= 0) return (recv_res);

    unpack_int(buffer_len, &(message->len));

    char *buffer = malloc(sizeof(char) * message->len);
    message->len = recv(this->sock, buffer, message->len, MSG_DONTWAIT);

    message->message = buffer;

    return (message->len);
}

void TClient_Start_Recv(TClient *this, TServer *server)
{
    if (this->is_receving == 0) {
        if (server)
            this->server = server;
        this->is_receving = 1;
        pthread_create(&(this->client_thread), NULL, TClient_Receving, (void*)this);
    }
}

void TClient_Stop_Recv(TClient *this)
{
    if (this->is_receving == 1) {
        this->is_receving = 0;
        pthread_join(this->client_thread, NULL);
        this->server = NULL;
    }
}

static void *TClient_Receving(void *p_args)
{
    TClient *client = (TClient*)p_args;

    while (client->is_receving && client->sock != -1) {
        TMessage message;
        int res_read = TClient_Recv(client, &message);

        pthread_mutex_lock(&mutex_message_event);
        if (res_read > 0) {
            if (client->On_Message)
                client->On_Message(client, message);
            else if (client->Server_On_Message && client->server)
                client->Server_On_Message(client, client->server, message);
        }
        if (!res_read) {
            if (client->On_Disconnect)
                client->On_Disconnect(client);
            else if (client->Server_On_Disconnect && client->server)
                client->Server_On_Disconnect(client, client->server);
            closesocket(client->sock);
            client->is_receving = 0;
            client->sock = -1;
            client->server = NULL;
        }
        pthread_mutex_unlock(&mutex_message_event);
    }

    client->is_receving = 0;
    return (NULL);
}

void TClient_Disconnect(TClient *this)
{
    if (this->sock != -1) {
        closesocket(this->sock);
        this->Stop_Recv(this);
        this->sock = -1;
    }
}

void TClient_New_Free(TClient *this)
{
    if (this) {
        this->Disconnect(this);
    }
    free(this);
}

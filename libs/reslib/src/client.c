/*
** ETNA PROJECT, 05/02/2019 by martin_h, hamide_a, despla_g, weber_w
** resLib
** File description:
**      Wrapper around the socket API.
*/

#include "client.h"

static void TClient_Init(TClient *this);

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
    this->Disconnect = TClient_Disconnect;

    this->sock = -1;
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

    int total = 0;
    int bytesleft = (int)(message.len);
    int n;

    while(total < (int)(message.len)) {
        n = send(this->sock, (message.message) + total, bytesleft, 0);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
    }

    return (n == -1 ? -1 : 0);
}

int TClient_Recv(TClient *this, TMessage *message)
{
    if (this->sock == -1)
        return (0);

    int nb_read = recv(this->sock, message->message, (int)(message->len), 0);

    return (nb_read);
}

void TClient_Disconnect(TClient *this)
{
    if (this->sock == -1) {
        closesocket(this->sock);
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

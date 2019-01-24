#include "sockets.h"
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

int TClient_Send(TClient *this, const void *buffer, size_t len)
{
    if(send(this->sock, buffer, len, 0) < 0)
        return (-1);
    return (0);
}

int TClient_Recv(TClient *this, void *buffer, size_t len)
{
    int n = recv(this->sock, buffer, len, 0);

    if(n < 0)
        return (-1);

    return 0;
}

void TClient_Disconnect(TClient *this)
{
    closesocket(this->sock);
}

void TClient_New_Free(TClient *this)
{
    if (this) {
        closesocket(this->sock);
        // free ressources here
    }
    free(this);
}

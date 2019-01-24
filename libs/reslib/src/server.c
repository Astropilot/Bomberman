#include "server.h"

static void TServer_Init(TServer *this);
static void TServer_AddClient_ToList(TServer *this, TSClient sock);
static void TServer_Free_Clients(TServer *this);

TServer *New_TServer(void)
{
    TServer *this = malloc(sizeof(TServer));

    if(!this) return NULL;
    TServer_Init(this);
    this->Free = TServer_New_Free;
    return this;
}

static void TServer_Init(TServer *this)
{
    this->Listen = TServer_Listen;
    this->AddClient_Async = TServer_AddClient_Async;
    this->SendTo_Async = TServer_SendTo_Async;
    this->server_sock = -1;
    this->clients_head = NULL;
}

int TServer_Listen(TServer *this, unsigned short int port, size_t max_c)
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN sin = { 0 };

    if(sock == INVALID_SOCKET)
        return -1;

    int flags = fcntl(sock, F_GETFL);;
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);

    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(port);
    sin.sin_family = AF_INET;

    if(bind(sock,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
        return -1;

    if(listen(sock, max_c) == SOCKET_ERROR)
        return -1;

    this->server_sock = sock;
    return (0);
}

void TServer_SendTo_Async(TServer *this, const void *buf, size_t len, TSClient client)
{
    //TODO: HERE
    return;
}

TSClient TServer_AddClient_Async(TServer *this)
{
    int client_socket = accept(this->server_sock, NULL, NULL);
    if (client_socket != -1) {
        TSClient client = {client_socket};
        TServer_AddClient_ToList(this, client);
        return (client);
    }
    return -1;
}

static void TServer_AddClient_ToList(TServer *this, TSClient sock)
{
    if (!this->clients_head) {
        TSClient_Node *client_node = malloc(sizeof(TSClient_Node));

        client_node->client = sock;
        client_node->next = NULL;
        this->clients_head = client_node;
    } else {
        TSClient_Node *current = this->clients_head;

        while (current->next != NULL)
            current = current->next;
        current->next = malloc(sizeof(TSClient_Node));
        current->next->client = sock;
        current->next->next = NULL;
    }
}

static void TServer_Free_Clients(TServer *this)
{
    TSClient_Node *current = this->clients_head;
    TSClient_Node *tmp = NULL;

    while (current != NULL) {
        closesocket(current->client->sock);

        tmp = current;
        current = current->next;
        free(tmp);
    }
}

void TServer_New_Free(TServer *this)
{
    if (this) {
        this->TServer_Free_Clients(this);
        closesocket(this->server_sock);
    }
    free(this);
}

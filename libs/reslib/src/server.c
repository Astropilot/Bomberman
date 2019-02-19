/*
** ETNA PROJECT, 05/02/2019 by martin_h, hamide_a, despla_g, weber_w
** resLib
** File description:
**      Wrapper around the socket API.
*/

#include "server.h"

static void TServer_Init(TServer *this, unsigned short int port, size_t max_c);
static void *TServer_Listenning(void *p_args);
static void TServer_Client_OnMessage(TClient *client, TServer *server, TMessage message);
static void TServer_Client_OnDisconnect(TClient *client, TServer *server);
static void TServer_RemoveClient(TServer *this, TClient *client);
static void TServer_AddClient(TServer *this, SOCKET sock);
static void TServer_Free_Clients(TServer *this);

TServer *New_TServer(unsigned short int port, size_t max_c)
{
    TServer *this = malloc(sizeof(TServer));

    if(!this) return NULL;
    TServer_Init(this, port, max_c);
    this->Free = TServer_New_Free;
    return this;
}

static void TServer_Init(TServer *this, unsigned short int port, size_t max_c)
{
    this->Start_Listenning = TServer_Start_Listenning;
    this->Stop_Listenning = TServer_Stop_Listenning;
    this->Send_Broadcast = TServer_Send_Broadcast;
    this->CountClients = TServer_CountClients;

    this->On_Connect = NULL;
    this->On_Message = NULL;
    this->On_Disconnect = NULL;

    this->max_c = max_c;
    this->is_listenning = 0;
    this->clients_head = NULL;
    this->server_sock = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN sin = { 0 };

    if(this->server_sock == INVALID_SOCKET)
        return;

    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(port);
    sin.sin_family = AF_INET;

    if(bind(this->server_sock,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
        return;

    if(listen(this->server_sock, this->max_c) == SOCKET_ERROR)
        return;
}

void TServer_Start_Listenning(TServer *this)
{
    this->is_listenning = 1;
    pthread_create(&(this->server_thread), NULL, TServer_Listenning, (void*)this);
}

void TServer_Stop_Listenning(TServer *this)
{
    this->is_listenning = 0;
    pthread_join(this->server_thread, NULL);
}

void TServer_Send_Broadcast(TServer *this, TMessage message)
{
    TClient_Node *current = this->clients_head;

    while (current != NULL) {
        TClient *client = New_TClient();
        client->sock = current->sock;
        client->Send(client, message);
        client->Free(client);
        current = current->next;
    }
}

static void *TServer_Listenning(void *p_args)
{
    TServer *server = (TServer*)p_args;
    fd_set rdfs;
    struct timeval timeout;

    while (server->is_listenning) {
        if (server->CountClients(server) < server->max_c) {
            timeout.tv_sec = 1;
            timeout.tv_usec = 0;

            FD_ZERO(&rdfs);
            FD_SET(server->server_sock, &rdfs);

            int res = select(server->server_sock + 1, &rdfs, NULL, NULL, &timeout);
            if (res <= 0)
                continue;
            if (FD_ISSET(server->server_sock, &rdfs)) {
                int client_socket = accept(server->server_sock, NULL, NULL);
                if (client_socket != SOCKET_ERROR) {
                    TClient *client = New_TClient();
                    client->sock = client_socket;
                    client->Server_On_Message = TServer_Client_OnMessage;
                    client->Server_On_Disconnect = TServer_Client_OnDisconnect;
                    TServer_AddClient(server, client_socket);
                    client->Start_Recv(client, server);
                    if (server->On_Connect)
                        server->On_Connect(server, client);
                }
            }
        }
    }

    return (NULL);
}

static void TServer_Client_OnMessage(TClient *client, TServer *server, TMessage message)
{
    if (server->On_Message)
        server->On_Message(server, client, message);
}

static void TServer_Client_OnDisconnect(TClient *client, TServer *server)
{
    if (server->On_Disconnect)
        server->On_Disconnect(server, client);
    TServer_RemoveClient(server, client);
}

static void TServer_RemoveClient(TServer *this, TClient *client)
{
    TClient_Node *current = this->clients_head;
    TClient_Node *previous = NULL;

    while (current != NULL) {
        if (current->sock == client->sock) {
            if (!previous)
                this->clients_head = current->next;
            else
                previous->next = current->next;
            closesocket(current->sock);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

size_t TServer_CountClients(TServer *this)
{
    TClient_Node *current = this->clients_head;
    size_t clients = 0;

    while (current != NULL) {
        clients++;
        current = current->next;
    }

    return (clients);
}

static void TServer_AddClient(TServer *this, SOCKET sock)
{
    if (!this->clients_head) {
        TClient_Node *client_node = malloc(sizeof(TClient_Node));

        client_node->sock = sock;
        client_node->next = NULL;
        this->clients_head = client_node;
    } else {
        TClient_Node *current = this->clients_head;

        while (current->next != NULL)
            current = current->next;
        current->next = malloc(sizeof(TClient_Node));
        current->next->sock = sock;
        current->next->next = NULL;
    }
}

static void TServer_Free_Clients(TServer *this)
{
    TClient_Node *current = this->clients_head;
    TClient_Node *tmp = NULL;

    while (current != NULL) {
        closesocket(current->sock);

        tmp = current;
        current = current->next;
        free(tmp);
    }
}

void TServer_New_Free(TServer *this)
{
    if (this) {
        this->Stop_Listenning(this);
        TServer_Free_Clients(this);
        closesocket(this->server_sock);
    }
    free(this);
}

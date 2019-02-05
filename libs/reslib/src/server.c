/*
** ETNA PROJECT, 05/02/2019 by martin_h, hamide_a, despla_g, weber_w
** resLib
** File description:
**      Wrapper around the socket API.
*/

#include "server.h"

static void TServer_Init(TServer *this, unsigned short int port, size_t max_c);
static void *TServer_Listenning(void *p_args);
static void *TServer_ClientThread(void *p_args);
static void TServer_RemoveClient(TServer *this, TClient *client);
static void TServer_AddClient(TServer *this, TClient *client, pthread_t thread);
static void TServer_Free_Clients(TServer *this);

static pthread_mutex_t mutex_message = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex_disconnect = PTHREAD_MUTEX_INITIALIZER;

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
        current->client->Send(current->client, message);
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
                //SOCKADDR_IN csin = { 0 };
                //size_t sinsize = sizeof(csin);

                int client_socket = accept(server->server_sock, NULL, NULL);
                if (client_socket != SOCKET_ERROR) {
                    TClient *client = New_TClient();
                    pthread_t thread_client;
                    params_t params = {server, client};
                    client->sock = client_socket;

                    pthread_create(&thread_client, NULL, TServer_ClientThread, (void*)&params);
                    TServer_AddClient(server, client, thread_client);
                    if (server->On_Connect)
                        server->On_Connect(server, client);
                }
            }
        }
    }

    return (NULL);
}

static void *TServer_ClientThread(void *p_args)
{
    params_t *params = (params_t*)p_args;
    TServer *server = params->server;
    TClient *client = params->client;
    unsigned int is_connected = 1;
    TMessage message;

    while (is_connected) {
        int res_read = client->Recv(client, &message);

        if (res_read == -1) // On error
            continue;
        if (res_read) {
            if (server->On_Message) {
                pthread_mutex_lock(&mutex_message);
                server->On_Message(server, client, message);
                pthread_mutex_unlock(&mutex_message);
            }
        } else {
            if (server->On_Disconnect) {
                pthread_mutex_lock(&mutex_disconnect);
                server->On_Disconnect(server, client);
                pthread_mutex_unlock(&mutex_disconnect);
            }
            // Disconnect user here
            is_connected = 0;
            TServer_RemoveClient(server, client);
        }
    }

    return (NULL);
}

static void TServer_RemoveClient(TServer *this, TClient *client)
{
    TClient_Node *current = this->clients_head;
    TClient_Node *previous = NULL;

    while (current != NULL) {
        if (current->client->sock == client->sock) {
            if (!previous)
                this->clients_head = current->next;
            else
                previous->next = current->next;
            current->client->Free(current->client);
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

static void TServer_AddClient(TServer *this, TClient *client, pthread_t thread)
{
    if (!this->clients_head) {
        TClient_Node *client_node = malloc(sizeof(TClient_Node));

        client_node->client = client;
        client_node->thread = thread;
        client_node->next = NULL;
        this->clients_head = client_node;
    } else {
        TClient_Node *current = this->clients_head;

        while (current->next != NULL)
            current = current->next;
        current->next = malloc(sizeof(TClient_Node));
        current->next->client = client;
        current->next->thread = thread;
        current->next->next = NULL;
    }
}

static void TServer_Free_Clients(TServer *this)
{
    TClient_Node *current = this->clients_head;
    TClient_Node *tmp = NULL;

    while (current != NULL) {
        current->client->Disconnect(current->client);
        pthread_join(current->thread, NULL);
        current->client->Free(current->client);

        tmp = current;
        current = current->next;
        free(tmp);
    }
}

void TServer_New_Free(TServer *this)
{
    if (this) {
        TServer_Free_Clients(this);
        this->Stop_Listenning(this);
        closesocket(this->server_sock);
    }
    free(this);
}

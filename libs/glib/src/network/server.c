/*******************************************************************************
* PROJECT: gLib
*
* AUTHORS: Yohann Martin, Aziz Hamide, Gauthier Desplanque, William Weber
*
* DATE CREATED: 01/16/2019
*
* Copyright (c) 2019 Yohann MARTIN (@Astropilot). All rights reserved.
*
* Licensed under the MIT License. See LICENSE file in the project root for full
* license information.
*******************************************************************************/

#include "network/server.h"

static void TServer_Init(TServer *this, unsigned short int port, unsigned int max_c);
static int TServer_Listenning(void *p_args);
static void TServer_Client_OnMessage(TClient *client, TServer *server, TMessage message);
static void TServer_AddClient(TServer *this, TClient *client);
static void TServer_Free_Clients(TServer *this);

TServer *New_TServer(unsigned short int port, unsigned int max_c)
{
    TServer *this = malloc(sizeof(TServer));

    if(!this) return (NULL);
    TServer_Init(this, port, max_c);
    this->Free = TServer_New_Free;
    return (this);
}

static void TServer_Init(TServer *this, unsigned short int port, unsigned int max_c)
{
    if (!this) return;

    this->Start_Listenning = TServer_Start_Listenning;
    this->Stop_Listenning = TServer_Stop_Listenning;
    this->Send_Broadcast = TServer_Send_Broadcast;
    this->CountClients = TServer_CountClients;
    this->Disconnect_Client = TServer_Disconnect_Client;

    this->On_Connect = NULL;
    this->On_Message = NULL;

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
    this->server_thread = NULL;
}

void TServer_Start_Listenning(TServer *this)
{
    if (!this) return;

    this->is_listenning = 1;
    this->server_thread = SDL_CreateThread(TServer_Listenning, "TServer_Listenning", (void*)this);
}

void TServer_Stop_Listenning(TServer *this)
{
    if (!this || !this->server_thread) return;

    this->is_listenning = 0;
    SDL_WaitThread(this->server_thread, NULL);
}

void TServer_Send_Broadcast(TServer *this, TMessage message)
{
    if (!this) return;

    TClient_Node *current = this->clients_head;

    while (current != NULL) {
        TMessage tmp_message = {message.len, NULL};

        if (current->client && current->client->Send) {
            tmp_message.message = malloc(sizeof(unsigned char) * message.len);
            if (tmp_message.message) {
                memcpy(tmp_message.message, message.message, message.len);
                current->client->Send(current->client, tmp_message);
            }
        }
        current = current->next;
    }
    free(message.message);
}

unsigned int TServer_CountClients(TServer *this)
{
    if (!this) return (0);

    TClient_Node *current = this->clients_head;
    unsigned int clients = 0;

    while (current != NULL) {
        clients++;
        current = current->next;
    }
    return (clients);
}

void TServer_Disconnect_Client(TServer *this, TClient *client)
{
    if (!this || !client) return;

    TClient_Node *current = this->clients_head;
    TClient_Node *previous = NULL;

    while (current != NULL) {
        if (current->client == client) {
            if (!previous)
                this->clients_head = current->next;
            else
                previous->next = current->next;

            if (current->client->Disconnect)
                current->client->Disconnect(current->client);
            if (current->client->Free)
                current->client->Free(current->client);

            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

static int TServer_Listenning(void *p_args)
{
    TServer *server = (TServer*)p_args;
    fd_set rdfs;
    struct timeval timeout;

    while (server && server->is_listenning) {
        if (server->CountClients(server) < server->max_c) {
            timeout.tv_sec = 1;
            timeout.tv_usec = 0;

            FD_ZERO(&rdfs);
            FD_SET(server->server_sock, &rdfs);

            int res = select((int)server->server_sock + 1, &rdfs, NULL, NULL, &timeout);
            if (res <= 0)
                continue;
            if (FD_ISSET(server->server_sock, &rdfs)) {
                SOCKET client_socket = accept(server->server_sock, NULL, NULL);
                if (client_socket != SOCKET_ERROR) {
                    TClient *client = New_TClient();

                    if (client) {
                        SocketNonBlocking(client_socket, 0);
                        client->sock = client_socket;
                        client->is_connected = 1;
                        client->Server_On_Message = TServer_Client_OnMessage;
                        TServer_AddClient(server, client);
                        client->Start_Recv(client, server);
                        if (server->On_Connect)
                            server->On_Connect(server, client);
                    }
                }
            }
        }
    }

    return (0);
}

static void TServer_Client_OnMessage(TClient *client, TServer *server, TMessage message)
{
    if (!client || !server) return;

    if (server->On_Message)
        server->On_Message(server, client, message);
}

static void TServer_AddClient(TServer *this, TClient *client)
{
    if (!this || !client) return;

    if (!this->clients_head) {
        TClient_Node *client_node = malloc(sizeof(TClient_Node));

        if (client_node) {
            client_node->client = client;
            client_node->next = NULL;
            this->clients_head = client_node;
        }
    } else {
        TClient_Node *current = this->clients_head;

        while (current->next != NULL)
            current = current->next;
        current->next = malloc(sizeof(TClient_Node));
        if (current->next) {
            current->next->client = client;
            current->next->next = NULL;
        }
    }
}

static void TServer_Free_Clients(TServer *this)
{
    if (!this) return;

    TClient_Node *current = this->clients_head;
    TClient_Node *tmp = NULL;

    while (current != NULL) {

        if (current->client->Disconnect)
            current->client->Disconnect(current->client);
        if (current->client->Free)
            current->client->Free(current->client);

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

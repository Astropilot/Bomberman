/*
** ETNA PROJECT, 05/02/2019 by martin_h, hamide_a, despla_g, weber_w
** resLib
** File description:
**      Wrapper around the socket API.
*/

#ifndef RESLIB_SERVER_H_
#define RESLIB_SERVER_H_

#include <stdlib.h>
#include <pthread.h>

#include "sockets.h"
#include "client.h"
#include "message.h"

typedef struct TClient_Node {
    SOCKET sock;
    struct TClient_Node *next;
} TClient_Node ;

typedef struct TServer {

    void(*Start_Listenning)(struct TServer*);

    void(*Stop_Listenning)(struct TServer*);

    void(*Send_Broadcast)(struct TServer*, TMessage);

    size_t(*CountClients)(struct TServer*);

    void(*Free)(struct TServer*);

    /* Callbacks */

    void(*On_Connect)(struct TServer*, TClient*);

    void(*On_Message)(struct TServer*, TClient*, TMessage);

    void(*On_Disconnect)(struct TServer*, TClient*);

    SOCKET server_sock;
    unsigned int is_listenning;
    size_t max_c;
    pthread_t server_thread;
    TClient_Node *clients_head;

} TServer ;

TServer* New_TServer(unsigned short int port, size_t max_c);
void TServer_Start_Listenning(TServer *this);
void TServer_Stop_Listenning(TServer *this);
void TServer_Send_Broadcast(TServer *this, TMessage message);
size_t TServer_CountClients(TServer *this);
void TServer_New_Free(TServer *this);

#endif

/*
** ETNA PROJECT, 05/02/2019 by martin_h, hamide_a, despla_g, weber_w
** resLib
** File description:
**      Wrapper around the socket API.
*/

#ifndef RESLIB_CLIENT_H_
#define RESLIB_CLIENT_H_

#include <stdlib.h>
#include <pthread.h>

#include "sockets.h"
#include "message.h"

typedef struct TServer TServer;

typedef struct TClient {

    int(*Connect)(struct TClient*, const char*, unsigned short int);

    int(*Send)(struct TClient*, TMessage);

    //int(*Recv)(struct TClient*, TMessage*);

    void(*Start_Recv)(struct TClient*, TServer*);

    void(*Stop_Recv)(struct TClient*);

    void(*Disconnect)(struct TClient*);

    void(*Free)(struct TClient*);

    /* Callbacks */

    void(*On_Message)(struct TClient*, TMessage);

    void(*Server_On_Message)(struct TClient*, TServer*, TMessage);

    SOCKET sock;
    unsigned int is_receving;
    pthread_t client_thread;
    TServer* server;

} TClient ;

TClient *New_TClient(void);
int TClient_Connect(TClient *this, const char *addr, unsigned short int port);
int TClient_Send(TClient *this, TMessage message);
void TClient_Start_Recv(TClient *this, TServer *server);
void TClient_Stop_Recv(TClient *this);
void TClient_Disconnect(TClient *this);
void TClient_New_Free(TClient *this);

#endif

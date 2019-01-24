/*
** ETNA PROJECT, 16/01/2019 by group
** gLib
** File description:
**      Graphic library with SDL2
*/

#ifndef RESLIB_SERVER_H_
#define RESLIB_SERVER_H_

#include <stdlib.h>

#include "reslib.h"

typedef struct TSClient {
   SOCKET sock;
} TSClient ;

typedef struct TSClient_Node {
    TSClient client;
    struct TSClient_Node *next;
}

typedef struct TServer {

    int(*Listen)(struct TServer*, unsigned short int, size_t);

    TSClient(*AddClient_Async)(struct TServer*);

    void(*SendTo_Async)(TServer*, const void*, size_t, TSClient);

    SOCKET server_sock; // int
    TSClient_Node *clients_head;

} TServer ;

TServer* New_TServer(void);
int TServer_Listen(TServer *this, unsigned short int port, size_t max_c);
TSClient TServer_AddClient_Async(TServer *this);
void TServer_SendTo_Async(TServer *this, const void *buf, size_t len, TSClient client);
void TServer_New_Free(TServer *this);

#endif

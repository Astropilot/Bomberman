/*
** ETNA PROJECT, 16/01/2019 by group
** gLib
** File description:
**      Graphic library with SDL2
*/

#ifndef RESLIB_CLIENT_H_
#define RESLIB_CLIENT_H_

#include <stdlib.h>

#include "sockets.h"

typedef struct TClient {

    int(*Connect)(struct TClient*, const char*, unsigned short int);

    int(*Send)(struct TClient*, const void*, size_t);

    int(*Recv)(struct TClient*, void*, size_t);

    void(*Disconnect)(struct TClient*);

    void(*Free)(struct TClient*);

    SOCKET sock; // int
    //fd_set rdfs;

} TClient ;

TClient *New_TClient(void);
int TClient_Connect(TClient *this, const char *addr, unsigned short int port);
int TClient_Send(TClient *this, const void *buffer, size_t len);
int TClient_Recv(TClient *this, void *buffer, size_t len);
void TClient_Disconnect(TClient *this);
void TClient_New_Free(TClient *this);

#endif

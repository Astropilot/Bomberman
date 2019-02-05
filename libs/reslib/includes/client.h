/*
** ETNA PROJECT, 05/02/2019 by martin_h, hamide_a, despla_g, weber_w
** resLib
** File description:
**      Wrapper around the socket API.
*/

#ifndef RESLIB_CLIENT_H_
#define RESLIB_CLIENT_H_

#include <stdlib.h>

#include "sockets.h"
#include "message.h"

typedef struct TClient {

    int(*Connect)(struct TClient*, const char*, unsigned short int);

    int(*Send)(struct TClient*, TMessage);

    int(*Recv)(struct TClient*, TMessage*);

    void(*Disconnect)(struct TClient*);

    void(*Free)(struct TClient*);

    SOCKET sock;

} TClient ;

TClient *New_TClient(void);
int TClient_Connect(TClient *this, const char *addr, unsigned short int port);
int TClient_Send(TClient *this, TMessage message);
int TClient_Recv(TClient *this, TMessage* message);
void TClient_Disconnect(TClient *this);
void TClient_New_Free(TClient *this);

#endif

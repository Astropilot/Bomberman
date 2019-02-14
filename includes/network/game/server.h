/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the game server component.
*/

#ifndef NETWORK_SERVER_H_
#define NETWORK_SERVER_H_

#include <stdlib.h>
#include <unistd.h>

#include "reslib.h"

typedef struct TGameServer {

    void(*Start)(struct TGameServer*);

    void(*Stop)(struct TGameServer*);

    void(*Free)(struct TGameServer*);

    TServer *server;
    int max_clients;

} TGameServer ;

TGameServer* New_TGameServer(int port, int max_clients);
void TGameServer_Start(TGameServer *this);
void TGameServer_Stop(TGameServer *this);
void TGameServer_New_Free(TGameServer *this);

#endif

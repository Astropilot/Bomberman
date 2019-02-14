/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the game client component.
*/

#ifndef NETWORK_CLIENT_H_
#define NETWORK_CLIENT_H_

#include <stdlib.h>
#include <unistd.h>

#include "reslib.h"

typedef struct TGameClient {

    void(*Join_Game)(struct TGameClient*, const char*, const char*, int);

    void(*Leave_Game)(struct TGameClient*);

    void(*Free)(struct TGameClient*);

    TClient client;
    char *username;

} TGameClient ;

TGameClient* New_TGameClient();
int TGameClient_Join_Game(TGameClient *this, const char *username, const char *ip, int port);
void TGameClient_Leave_Game(TGameClient *this);
void TGameClient_New_Free(TGameClient *this);

#endif

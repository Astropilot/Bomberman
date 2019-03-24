/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the game client component.
*/

#ifndef NETWORK_CLIENT_H_
#define NETWORK_CLIENT_H_

#include <stdlib.h>

#include "network/network.h"
#include "glib.h"
#include "network/game/server.h"
#include "core/player.h"

typedef struct TGameClient {

    TFrame*(*Register_Frame)(struct TGameClient*, TFrame*);

    void(*Ready)(struct TGameClient*);

    void(*Move)(struct TGameClient*, direction_t);

    void(*Place_Bomb)(struct TGameClient*);

    void(*Handle_Messages)(struct TGameClient*);

    void(*Leave_Game)(struct TGameClient*);

    void(*Free)(struct TGameClient*);

    TClient *client;
    TGameServer *gameserver;
    TFrame *game_frame;
    unsigned int is_owner;
    int player;
    unsigned int bomb_offset;

} TGameClient ;

TGameClient* New_TGameClient();
TFrame *TGameClient_Register_Frame(TGameClient *this, TFrame *frame);
void TGameClient_Ready(TGameClient *this);
void TGameClient_Move(TGameClient *this, direction_t direction);
void TGameClient_Place_Bomb(TGameClient *this);
void TGameClient_Handle_Messages(TGameClient *this);
void TGameClient_Leave_Game(TGameClient *this);
void TGameClient_New_Free(TGameClient *this);

#endif

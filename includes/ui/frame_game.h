/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the game frame.
*/

#ifndef FRAME_GAME_H_
#define FRAME_GAME_H_

#include "glib.h"
#include "network/game/client.h"

TFrame* New_GameFrame(TGameClient *m_gameclient);
void GameFrame_UpdatePlayerInfo(TFrame *frame, player_t player);

#endif

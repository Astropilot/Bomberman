/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the lobby frame.
*/

#ifndef FRAME_LOBBY_H_
#define FRAME_LOBBY_H_

#include <stdio.h>
#include <stdarg.h>

#include "glib.h"
#include "network/game/lobby.h"

TFrame* New_LobbyFrame(TLobbyClient *m_lobbyclient);

#endif

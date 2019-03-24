/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the lobby client component.
*/

#ifndef NETWORK_LOBBY_H_
#define NETWORK_LOBBY_H_

#include <stdlib.h>

#include "network/network.h"
#include "glib.h"
#include "network/game/server.h"

typedef struct TLobbyClient {

    TFrame*(*Register_Frame)(struct TLobbyClient*, TFrame*);

    void(*Start_Server)(struct TLobbyClient*, int, int);

    void(*Join_Lobby)(struct TLobbyClient*, const char*, const char*, int);

    void(*Start_Game)(struct TLobbyClient*);

    void(*Handle_Messages)(struct TLobbyClient*);

    void(*Leave_Lobby)(struct TLobbyClient*);

    void(*Free)(struct TLobbyClient*);

    TClient *client;
    TGameServer *gameserver;
    TFrame *lobby_frame;
    char *username;
    unsigned int is_owner;
    int player;
    unsigned int nb_players;

} TLobbyClient ;

TLobbyClient* New_TLobbyClient();
TFrame *TLobbyClient_Register_Frame(TLobbyClient *this, TFrame *frame);
void TLobbyClient_Start_Server(TLobbyClient *this, int port, int max_clients);
void TLobbyClient_Join_Lobby(TLobbyClient *this, const char *username, const char *ip, int port);
void TLobbyClient_Start_Game(TLobbyClient *this);
void TLobbyClient_Handle_Messages(TLobbyClient *this);
void TLobbyClient_Leave_Lobby(TLobbyClient *this);
void TLobbyClient_New_Free(TLobbyClient *this);

#endif

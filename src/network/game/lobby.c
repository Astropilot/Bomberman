/*******************************************************************************
* PROJECT: Bomberman
*
* AUTHORS: Yohann Martin, Aziz Hamide, Gauthier Desplanque, William Weber
*
* DATE CREATED: 01/16/2019
*
* Copyright (c) 2019 Yohann MARTIN (@Astropilot). All rights reserved.
*
* Licensed under the MIT License. See LICENSE file in the project root for full
* license information.
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "glib.h"
#include "logic/lobby.h"
#include "network/game/lobby.h"
#include "network/network.h"
#include "network/game/server.h"
#include "network/packets/packet.h"
#include "network/packets/packet_req_connect.h"
#include "network/packets/packet_req_startgame.h"
#include "network/packets/packet_disconnect.h"


TLobbyClient* New_TLobbyClient()
{
    TLobbyClient *this = malloc(sizeof(TLobbyClient));

    if(!this) return (NULL);

    this->client = NULL;
    this->gameserver = NULL;
    this->lobby_scene = NULL;
    this->is_owner = 0;
    this->player = -1;
    this->nb_players = 0;
    this->Register_Scene = TLobbyClient_Register_Scene;
    this->Start_Server = TLobbyClient_Start_Server;
    this->Join_Lobby = TLobbyClient_Join_Lobby;
    this->Start_Game = TLobbyClient_Start_Game;
    this->Handle_Messages = TLobbyClient_Handle_Messages;
    this->Leave_Lobby = TLobbyClient_Leave_Lobby;
    this->Free = TLobbyClient_New_Free;
    return (this);
}

TScene *TLobbyClient_Register_Scene(TLobbyClient *this, TScene *scene)
{
    this->lobby_scene = scene;
    return (scene);
}

void TLobbyClient_Start_Server(TLobbyClient *this, int port, game_rules_t rules)
{
    if (!this) return;
    this->is_owner = 1;
    this->rules = rules;
    this->gameserver = New_TGameServer(rules);
    if (this->gameserver)
        this->gameserver->Start(this->gameserver, port);
}

void TLobbyClient_Join_Lobby(TLobbyClient *this, const char *username, const char *ip, int port)
{
    if (!this || !username || !ip) return;

    this->client = New_TClient();

    if (!this->client) return;
    int res = this->client->Connect(this->client, ip, port);
    if (res != 0) {
        this->Leave_Lobby(this);
    } else {
        TReqConnectPacket *p_rc = New_TReqConnectPacket(NULL);

        p_rc->player_name = strdup(username);
        this->client->Send(this->client, packet_to_message((TPacket*)p_rc, 1));
    }
}

void TLobbyClient_Start_Game(TLobbyClient *this)
{
    TReqStartGamePacket *p_rs = New_TReqStartGamePacket(NULL);

    p_rs->player = this->player;
    this->client->Send(this->client, packet_to_message((TPacket*)p_rs, 1));
}

void TLobbyClient_Handle_Messages(TLobbyClient *this)
{
    if (!this->client)
        return;

    TMessage message;
    int packet_id;
    int res_read = this->client->Recv(this->client, &message);
    #ifdef _WIN32
        if (res_read == WSAEWOULDBLOCK || res_read == EAGAIN || message.len <= 0) return;
    #else
        if (res_read == EWOULDBLOCK || res_read == EAGAIN || message.len <= 0) return;
    #endif

    packet_id = extract_packet_id(message.message);
    handle_lobby_logic(this, message, packet_id);
}

void TLobbyClient_Leave_Lobby(TLobbyClient *this)
{
    if (!this || !this->client)
        return;

    if (this->player != -1) {
        TReqDisconnectPacket *p_d = New_TReqDisconnectPacket(NULL);

        p_d->reason = (this->is_owner ? MASTER_LEAVE : USER_QUIT);
        p_d->player = (unsigned int)this->player;
        this->client->Send(this->client, packet_to_message((TPacket*)p_d, 1));
    }
    this->client->Disconnect(this->client);
    this->client->Free(this->client);
    this->client = NULL;
    this->is_owner = 0;
    this->player = -1;
    this->nb_players = 0;
    if (this->gameserver) {
        this->gameserver->Stop(this->gameserver);
        this->gameserver->Free(this->gameserver);
        this->gameserver = NULL;
    }
    this->lobby_scene->window->Show_Scene(this->lobby_scene->window, "SCENE_MAIN_MENU", 0);
}

void TLobbyClient_New_Free(TLobbyClient *this)
{
    free(this);
}

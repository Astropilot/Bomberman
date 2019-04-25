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
#include "network/packets/packet_ack_connect.h"
#include "network/packets/packet_ack_lobbystate.h"
#include "network/packets/packet_disconnect.h"

static void handle_connect(TLobbyClient *lobby, TMessage message);
static void handle_disconnect(TLobbyClient *lobby, TMessage message);
static void handle_lobbystate(TLobbyClient *lobby, TMessage message);
static void handle_startgame(TLobbyClient *lobby, TMessage message);

static void (*message_handler[])(TLobbyClient*, TMessage) = {
    [ACK_CONNECT] = handle_connect,
    [ACK_DISCONNECT] = handle_disconnect,
    [ACK_LOBBY_STATE] = handle_lobbystate,
    [ACK_START_GAME] = handle_startgame
};

void handle_lobby_logic(TLobbyClient *lobby, TMessage message, int packet_id)
{
    if (!lobby) return;

    (*message_handler[packet_id])(lobby, message);
}

static void handle_connect(TLobbyClient *lobby, TMessage message)
{
    TAckConnectPacket *p_ac = New_TAckConnectPacket(message.message);
    p_ac->Unserialize(p_ac);

    if (p_ac->status != OK) {
        lobby->player = -1;
        lobby->Leave_Lobby(lobby, 0);
    } else
        lobby->player = (int)p_ac->player;
    p_ac->Free(p_ac);
}

static void handle_disconnect(TLobbyClient *lobby, TMessage message)
{
    free(message.message);
    lobby->Leave_Lobby(lobby, 0);
}

static void handle_lobbystate(TLobbyClient *lobby, TMessage message)
{
    TText *txt_label = NULL;
    TAckLobbyStatePacket *p_as = New_TAckLobbyStatePacket(message.message);
    unsigned int i;

    p_as->Unserialize(p_as);
    lobby->nb_players = p_as->nb_players;
    char *status = malloc(sizeof(char) * 255);
    sprintf(status, "Nombre de joueurs presents: %d/%d", lobby->nb_players, MAX_PLAYERS);

    txt_label = (TText*)lobby->lobby_scene->Get_Drawable(lobby->lobby_scene, "LABEL_STATUS");
    txt_label->Change_Text(txt_label, lobby->lobby_scene, status);
    txt_label->pos.x = (WIN_WIDTH / 2) - (txt_label->pos.w / 2);
    txt_label->pos.y = 585;

    lobby->lobby_scene->Free_Drawables(lobby->lobby_scene, "LABEL_USERNAME");

    for (i = 0; i < MAX_PLAYERS; i++) {
        sprintf(status, "BTN_KICK_%u", i);
        TButton *btn_kick = (TButton*)lobby->lobby_scene->Get_Drawable(
            lobby->lobby_scene, status
        );

        btn_kick->is_visible = 0;
    }

    for (i = 0; i < lobby->nb_players; i++) {
        SDL_Rect pos_username = {0, 0, 0, 0};
        SDL_Color color = {255, 255, 255, 255};
        TTF_Font *font = loadFont(FONT_PATH "fixedsys.ttf", 24);
        TText *txt_username = New_TText(
            lobby->lobby_scene, p_as->players[i].username, font, color, pos_username
        );

        txt_username->pos.x = 446;
        txt_username->pos.y = 216 + (p_as->players[i].p_id * 92) - (txt_username->pos.h / 2);
        lobby->lobby_scene->Add_Drawable(
            lobby->lobby_scene, (TDrawable*)txt_username,
            "LABEL_USERNAME", 1, GLIB_FREE_ON_UNLOAD
        );

        if (lobby->is_owner && (int)p_as->players[i].p_id != lobby->player) {
            sprintf(status, "BTN_KICK_%u", p_as->players[i].p_id);
            TButton *btn_kick = (TButton*)lobby->lobby_scene->Get_Drawable(
                lobby->lobby_scene, status
            );

            btn_kick->is_visible = 1;
        }
    }

    free(status);
    p_as->Free(p_as);
}

static void handle_startgame(TLobbyClient *lobby, TMessage message)
{
    TClient *client_tmp = lobby->client;

    free(message.message);
    lobby->client = NULL;
    lobby->lobby_scene->window->Show_Scene(
        lobby->lobby_scene->window,
        "SCENE_GAME",
        4, client_tmp, lobby->gameserver, lobby->player, lobby->nb_players
    );
}

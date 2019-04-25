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
#include "logic/server.h"
#include "core/map.h"
#include "network/game/server.h"
#include "network/network.h"
#include "network/packets/packet.h"
#include "network/packets/packet_ack_connect.h"
#include "network/packets/packet_ack_lobbystate.h"
#include "network/packets/packet_ack_startgame.h"
#include "network/packets/packet_ack_gameinit.h"
#include "network/packets/packet_ack_move.h"
#include "network/packets/packet_ack_placebomb.h"
#include "network/packets/packet_ack_playerupdate.h"
#include "network/packets/packet_ack_endgame.h"
#include "network/packets/packet_disconnect.h"
#include "network/packets/packet_req_connect.h"
#include "network/packets/packet_req_move.h"
#include "network/packets/packet_req_placebomb.h"
#include "network/packets/packet_req_startgame.h"
#include "network/packets/packet_req_kickplayer.h"
#include "network/packets/packet_req_ready.h"

static void handle_disconnect(TGameServer*, TClient*, TMessage);
static void handle_connect(TGameServer*, TClient*, TMessage);
static void handle_startgame(TGameServer*, TClient*, TMessage);
static void handle_kickplayer(TGameServer*, TClient*, TMessage);
static void handle_ready(TGameServer*, TClient*, TMessage);
static void handle_move(TGameServer*, TClient*, TMessage);
static void handle_placebomb(TGameServer*, TClient*, TMessage);

static void (*message_handler[])(TGameServer*, TClient*, TMessage) = {
    [REQ_DISCONNECT] = handle_disconnect,
    [REQ_CONNECT] = handle_connect,
    [REQ_START_GAME] = handle_startgame,
    [REQ_READY] = handle_ready,
    [REQ_MOVE] = handle_move,
    [REQ_PLACE_BOMB] = handle_placebomb,
    [REQ_KICK_PLAYER] = handle_kickplayer
};

void handle_server_logic(TGameServer *server, TClient *client, TMessage message, int packet_id)
{
    if (!server) return;

    (*message_handler[packet_id])(server, client, message);
}

static void handle_disconnect(TGameServer *game_server, TClient* client, TMessage message)
{
    TReqDisconnectPacket *p_d = New_TReqDisconnectPacket(message.message);
    p_d->Unserialize(p_d);

    if (p_d->player >= (unsigned int)game_server->nb_players) {
        p_d->Free(p_d);
        return;
    }
    reset_player(&(game_server->map->players[p_d->player]));
    game_server->player_socks[p_d->player] = NULL;
    if (p_d->player != 0 && !game_server->game_started) {
        TAckLobbyStatePacket *p = New_TAckLobbyStatePacket(NULL);

        game_server->nb_players--;
        p->nb_players = (int)game_server->nb_players;
        p->players = game_server->map->players;
        game_server->server->Send_Broadcast(
            game_server->server,
            packet_to_message((TPacket*)p, 1)
        );
    }
    (void)client;
    p_d->Free(p_d);
}

static void handle_connect(TGameServer *game_server, TClient* client, TMessage message)
{
    TReqConnectPacket *p_rc = New_TReqConnectPacket(message.message);
    p_rc->Unserialize(p_rc);

    if (game_server->game_started) {
        TAckConnectPacket *p_a = New_TAckConnectPacket(NULL);
        p_a->status = GAME_STARTED;
        p_a->player = MAX_PLAYERS + 1;
        client->Send(client, packet_to_message((TPacket*)p_a, 1));
        p_rc->Free(p_rc);
        return;
    }

    if (game_server->nb_players < game_server->rules.max_players) {
        TAckConnectPacket *p_a = New_TAckConnectPacket(NULL);
        TAckLobbyStatePacket *p = New_TAckLobbyStatePacket(NULL);

        p_a->status = OK;
        p_a->player = next_id(game_server->map->players);
        init_player(&(game_server->map->players[p_a->player]), p_a->player, p_rc->player_name);
        game_server->player_socks[p_a->player] = client;
        client->Send(client, packet_to_message((TPacket*)p_a, 1));

        game_server->nb_players++;
        p->nb_players = game_server->nb_players;
        p->players = game_server->map->players;
        game_server->server->Send_Broadcast(
            game_server->server,
            packet_to_message((TPacket*)p, 1)
        );
    } else {
        TAckConnectPacket *p_a = New_TAckConnectPacket(NULL);
        p_a->status = GAME_FULL;
        p_a->player = MAX_PLAYERS + 1;
        client->Send(client, packet_to_message((TPacket*)p_a, 1));
    }

    p_rc->Free(p_rc);
}

static void handle_startgame(TGameServer *game_server, TClient* client, TMessage message)
{
    TReqStartGamePacket *p_rs = New_TReqStartGamePacket(message.message);
    p_rs->Unserialize(p_rs);

    if (p_rs->player == 0) {
        TAckStartGamePacket *p = New_TAckStartGamePacket(NULL);

        game_server->map->Generate(game_server->map, game_server->rules.chance_breakable_wall);
        game_server->server->Send_Broadcast(
            game_server->server,
            packet_to_message((TPacket*)p, 1)
        );
    }
    (void)client;
    p_rs->Free(p_rs);
}

static void handle_kickplayer(TGameServer *game_server, TClient* client, TMessage message)
{
    TReqKickPlayerPacket *p_kp = New_TReqKickPlayerPacket(message.message);
    p_kp->Unserialize(p_kp);

    if (p_kp->player == 0 && p_kp->kick_id > 0) {
        TAckDisconnectPacket *p_d = New_TAckDisconnectPacket(NULL);
        TAckLobbyStatePacket *p_ls = New_TAckLobbyStatePacket(NULL);

        p_d->reason = KICKED_BY_MASTER;
        if (game_server->player_socks[p_kp->kick_id]) {
            game_server->player_socks[p_kp->kick_id]->Send(
                game_server->player_socks[p_kp->kick_id],
                packet_to_message((TPacket*)p_d, 1)
            );
        }
        reset_player(&(game_server->map->players[p_kp->kick_id]));



        game_server->nb_players--;
        p_ls->nb_players = (int)game_server->nb_players;
        p_ls->players = game_server->map->players;
        game_server->server->Send_Broadcast(
            game_server->server,
            packet_to_message((TPacket*)p_ls, 1)
        );
    }
    (void)client;
    p_kp->Free(p_kp);
}

static void handle_ready(TGameServer *game_server, TClient* client, TMessage message)
{
    TReqReadyPacket *p_rr = New_TReqReadyPacket(message.message);
    p_rr->Unserialize(p_rr);

    game_server->ready_players++;

    if (game_server->ready_players == game_server->nb_players) {
        TAckGameInitPacket *p = New_TAckGameInitPacket(NULL);

        p->nb_players = (unsigned int)game_server->nb_players;
        p->players = game_server->map->players;
        p->block_map = game_server->map->block_map;
        game_server->server->Send_Broadcast(
            game_server->server,
            packet_to_message((TPacket*)p, 1)
        );
        game_server->game_started = 1;
    }
    (void)client;
    p_rr->Free(p_rr);
}

static void handle_move(TGameServer *game_server, TClient* client, TMessage message)
{
    TReqMovePlayerPacket *p_rm = New_TReqMovePlayerPacket(message.message);
    unsigned int take_extra;
    p_rm->Unserialize(p_rm);

    player_t p_tmp = game_server->map->players[p_rm->player];
    take_extra = game_server->map->Move_Player(game_server->map, p_rm->player, p_rm->dir);
    player_t p_new = game_server->map->players[p_rm->player];

    if (p_tmp.pos.x != p_new.pos.x || p_tmp.pos.y != p_new.pos.y || p_tmp.direction != p_new.direction) {
        TAckMovePacket *p = New_TAckMovePacket(NULL);

        p->player_id = p_rm->player;
        p->player = game_server->map->players[p_rm->player];
        p->take_extra = take_extra;
        game_server->server->Send_Broadcast(
            game_server->server,
            packet_to_message((TPacket*)p, 1)
        );
        if (take_extra) {
            TAckPlayerUpdatePacket *p_pu = New_TAckPlayerUpdatePacket(NULL);

            p_pu->player = game_server->map->players[p_rm->player];
            game_server->server->Send_Broadcast(
                game_server->server,
                packet_to_message((TPacket*)p_pu, 1)
            );
        }
    }
    (void)client;
    p_rm->Free(p_rm);
}

static void handle_placebomb(TGameServer *game_server, TClient* client, TMessage message)
{
    TReqPlaceBombPacket *p_rb = New_TReqPlaceBombPacket(message.message);
    TAckPlaceBombPacket *p_ab = New_TAckPlaceBombPacket(NULL);
    p_rb->Unserialize(p_rb);

    player_t player = game_server->map->players[p_rb->player];
    p_ab->status = game_server->map->Place_Bomb(game_server->map, p_rb->player, &p_ab->reason);

    p_ab->x = player.pos.x;
    p_ab->y = player.pos.y;

    if (p_ab->status == BOMB_POSED) {
        TAckPlayerUpdatePacket *p_pu = New_TAckPlayerUpdatePacket(NULL);

        p_ab->bomb_id = game_server->map->bomb_offset - 1;
        p_pu->player = game_server->map->players[p_rb->player];

        game_server->server->Send_Broadcast(
            game_server->server,
            packet_to_message((TPacket*)p_ab, 1)
        );
        game_server->server->Send_Broadcast(
            game_server->server,
            packet_to_message((TPacket*)p_pu, 1)
        );
    } else
        client->Send(client, packet_to_message((TPacket*)p_ab, 1));

    p_rb->Free(p_rb);
}

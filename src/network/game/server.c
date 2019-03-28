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
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#include "main.h"
#include "core/map.h"
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
#include "network/packets/packet_req_ready.h"
#include "network/game/server.h"

static int TGameServer_Gameloop(void *p_args);
static void On_Message(TServer *server, TClient *client, TMessage message);

static TGameServer *game_server;

TGameServer* New_TGameServer()
{
    TGameServer *this = malloc(sizeof(TGameServer));

    if(!this) return NULL;

    game_server = this;
    this->server = NULL;
    this->max_clients = 0;
    this->nb_players = 0;
    this->ready_players = 0;
    this->map = NULL;
    this->is_listenning = 0;
    this->server_thread = NULL;
    this->game_started = 0;
    this->Start = TGameServer_Start;
    this->Stop = TGameServer_Stop;
    this->Free = TGameServer_New_Free;
    return this;
}

void TGameServer_Start(TGameServer *this, int port, int max_clients)
{
    this->server = New_TServer(port, 15);
    this->server->On_Message = On_Message;
    this->max_clients = max_clients;
    this->map = New_TMap((size_t)max_clients);
    this->nb_players = 0;
    this->ready_players = 0;
    this->game_started = 0;
    this->server->Start_Listenning(this->server);
    this->is_listenning = 1;
    this->server_thread = SDL_CreateThread(TGameServer_Gameloop, "TGameServer_Gameloop", NULL);
}

void TGameServer_Stop(TGameServer *this)
{
    if (!this->server)
        return;
    TAckDisconnectPacket *p = New_TAckDisconnectPacket(NULL);

    this->is_listenning = 0;
    this->game_started = 0;
    SDL_WaitThread(this->server_thread, NULL);
    p->reason = MASTER_LEAVE;
    this->server->Send_Broadcast(this->server, packet_to_message((TPacket*)p, 1));
    this->server->Free(this->server);
    this->server = NULL;
    this->map->Free(this->map);
    this->map = NULL;
}

static int TGameServer_Gameloop(void *p_args)
{
    unsigned int current_time = 0;
    unsigned int game_on = 1;

    while (game_server->is_listenning && game_on) {
        if (!game_server->game_started)
            continue;
        bomb_node_t *current_bomb = game_server->map->bombs_head;
        bomb_t *tmp_bomb = NULL;
        unsigned int players_alive = 0;

        current_time = SDL_GetTicks();
        while (current_bomb != NULL) {
            if (current_time >= current_bomb->bomb->time_explode) {
                game_server->map->Explose_Bomb(game_server->map, current_bomb->bomb, game_server->server);

                tmp_bomb = current_bomb->bomb;
                current_bomb = current_bomb->next;
                remove_bomb(&(game_server->map->bombs_head), tmp_bomb);
                free(tmp_bomb);
            } else
                current_bomb = current_bomb->next;
        }

        players_alive = alive_players(game_server->map->players);
        if (players_alive < 2) {
            TAckEndGamePacket *p = New_TAckEndGamePacket(NULL);

            if (players_alive == 1) {
                p->game_result = WINNER;
                p->winner = get_first_alive_player(game_server->map->players);
            } else if (players_alive == 0) {
                p->game_result = DRAW;
                p->winner = NULL;
            }
            game_server->server->Send_Broadcast(game_server->server, packet_to_message((TPacket*)p, 1));
            game_on = 0;
        }
    }
    (void) p_args;
    return (0);
}

void On_Message(TServer *server, TClient *client, TMessage message)
{
    int packet_id = extract_packet_id(message.message);
    switch (packet_id) {
        case REQ_DISCONNECT:;
            TReqDisconnectPacket *p_d = New_TReqDisconnectPacket(message.message);
            p_d->Unserialize(p_d);

            if (p_d->player >= server->CountClients(server)) {
                p_d->Free(p_d);
                break;
            }
            reset_player(&(game_server->map->players[p_d->player]));
            if (p_d->player != 0 && !game_server->game_started) {
                TAckLobbyStatePacket *p = New_TAckLobbyStatePacket(NULL);

                game_server->nb_players--;
                p->nb_players = (int)game_server->nb_players;
                server->Send_Broadcast(server, packet_to_message((TPacket*)p, 1));
            }
            p_d->Free(p_d);
            break;
        case REQ_CONNECT:;
            TReqConnectPacket *p_rc = New_TReqConnectPacket(message.message);
            p_rc->Unserialize(p_rc);

            int nb_clients = (int)server->CountClients(server);
            if (nb_clients <= game_server->max_clients) {
                TAckConnectPacket *p_a = New_TAckConnectPacket(NULL);
                TAckLobbyStatePacket *p = New_TAckLobbyStatePacket(NULL);

                p_a->status = OK;
                p_a->player = next_id(game_server->map->players);
                init_player(&(game_server->map->players[p_a->player]), p_a->player, p_rc->player_name);
                client->Send(client, packet_to_message((TPacket*)p_a, 1));

                game_server->nb_players++;
                p->nb_players = game_server->nb_players;
                server->Send_Broadcast(server, packet_to_message((TPacket*)p, 1));
            } else {
                TAckConnectPacket *p_a = New_TAckConnectPacket(NULL);
                p_a->status = GAME_FULL;
                p_a->player = MAX_PLAYERS + 1;
                client->Send(client, packet_to_message((TPacket*)p_a, 1));
            }

            p_rc->Free(p_rc);
            break;
        case REQ_START_GAME:;
            TReqStartGamePacket *p_rs = New_TReqStartGamePacket(message.message);
            p_rs->Unserialize(p_rs);

            if (p_rs->player == 0) {
                TAckStartGamePacket *p = New_TAckStartGamePacket(NULL);

                game_server->map->Generate(game_server->map);
                server->Send_Broadcast(server, packet_to_message((TPacket*)p, 1));
            }

            p_rs->Free(p_rs);
            break;
        case REQ_READY:;
            TReqReadyPacket *p_rr = New_TReqReadyPacket(message.message);
            p_rr->Unserialize(p_rr);

            game_server->ready_players++;

            if (game_server->ready_players == game_server->nb_players) {
                TAckGameInitPacket *p = New_TAckGameInitPacket(NULL);

                p->nb_players = (unsigned int)game_server->nb_players;
                p->players = game_server->map->players;
                p->block_map = game_server->map->block_map;
                server->Send_Broadcast(server, packet_to_message((TPacket*)p, 1));
                game_server->game_started = 1;
            }

            p_rr->Free(p_rr);
            break;
        case REQ_MOVE:;
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
                server->Send_Broadcast(server, packet_to_message((TPacket*)p, 1));
                if (take_extra) {
                    TAckPlayerUpdatePacket *p_pu = New_TAckPlayerUpdatePacket(NULL);

                    p_pu->player = game_server->map->players[p_rm->player];
                    server->Send_Broadcast(server, packet_to_message((TPacket*)p_pu, 1));
                }
            }

            p_rm->Free(p_rm);
            break;
        case REQ_PLACE_BOMB:;
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

                server->Send_Broadcast(server, packet_to_message((TPacket*)p_ab, 1));
                server->Send_Broadcast(server, packet_to_message((TPacket*)p_pu, 1));
            } else
                client->Send(client, packet_to_message((TPacket*)p_ab, 1));

            p_rb->Free(p_rb);
            break;
        default:
            free(message.message);
    }
}

void TGameServer_New_Free(TGameServer *this)
{
    if (this) {
        if (this->map)
            this->map->Free(this->map);
    }
    free(this);
}

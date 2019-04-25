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
#include "logic/server.h"
#include "core/map.h"
#include "core/minion.h"
#include "network/game/server.h"
#include "network/network.h"
#include "network/packets/packet.h"
#include "network/packets/packet_ack_endgame.h"
#include "network/packets/packet_disconnect.h"

static int TGameServer_Gameloop(void *p_args);
static void On_Message(TServer *server, TClient *client, TMessage message);

static TGameServer *game_server;

TGameServer* New_TGameServer(game_rules_t rules)
{
    TGameServer *this = malloc(sizeof(TGameServer));

    if(!this) return (NULL);

    game_server = this;
    this->server = NULL;
    this->nb_players = 0;
    this->ready_players = 0;
    this->map = NULL;
    this->is_listenning = 0;
    this->server_thread = NULL;
    this->game_started = 0;
    this->rules = rules;
    this->Start = TGameServer_Start;
    this->Stop = TGameServer_Stop;
    this->Free = TGameServer_New_Free;
    return (this);
}

void TGameServer_Start(TGameServer *this, int port)
{
    if (!this) return;

    this->server = New_TServer(port, 15);
    this->server->On_Message = On_Message;
    this->map = New_TMap(MAX_PLAYERS);
    this->nb_players = 0;
    this->ready_players = 0;
    this->game_started = 0;
    this->server->Start_Listenning(this->server);
    this->is_listenning = 1;
    this->server_thread = SDL_CreateThread(TGameServer_Gameloop, "TGameServer_Gameloop", NULL);
}

void TGameServer_Stop(TGameServer *this)
{
    if (!this || !this->server) return;

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

    while (game_server && game_server->is_listenning && game_on) {
        if (!game_server->game_started)
            continue;
        bomb_node_t *current_bomb = game_server->map->bombs_head;
        bomb_t *tmp_bomb = NULL;
        unsigned int players_alive = 0;

        current_time = SDL_GetTicks();

        minion_handle_logic(game_server->map->minion, current_time, game_server);

        while (current_bomb != NULL) {
            if (current_time >= current_bomb->bomb->time_explode) {
                game_server->map->Explose_Bomb(game_server->map, current_bomb->bomb, game_server);

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
    if (!server || !client) return;

    int packet_id = extract_packet_id(message.message);
    handle_server_logic(game_server, client, message, packet_id);
}

void TGameServer_New_Free(TGameServer *this)
{
    if (this) {
        if (this->map && this->map->Free)
            this->map->Free(this->map);
    }
    free(this);
}

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

#include <stdlib.h>

#include "main.h"
#include "core/minion.h"
#include "core/utils.h"
#include "pathfinding/pathfinding.h"
#include "network/game/server.h"
#include "network/network.h"
#include "network/packets/packet.h"
#include "network/packets/packet_ack_minionupdate.h"
#include "network/packets/packet_ack_playerupdate.h"

static int distance_manhattan(pos_t pos1, pos_t pos2)
{
    return ( abs(pos1.x - pos2.x) + abs(pos1.y - pos2.y) );
}

static int node_cost(int x, int y)
{
    if (y % 2 != 0 && x % 2 != 0)
        return (-1);
    return (1);
}

void init_minion(minion_t *minion)
{
    if (!minion) return;

    minion->pos.x = MAP_WIDTH / 2;
    minion->pos.y = MAP_HEIGHT / 2;
    minion->heal = 10;
    minion->heal_speed = 6000;
    minion->target_id = -1;
    minion->move_speed = 600;
    minion->last_move_time = 0;
    minion->last_heal_time = 0;
}

void minion_handle_logic(minion_t *minion, unsigned int current_time, TGameServer *game_server)
{
    // Movement
    if (current_time > minion->last_move_time + minion->move_speed) {
        if (minion->target_id == -1) {
            minion->target_id = get_nearest_player(*minion, game_server->map->players);
        }
        if (minion->target_id != -1) {
            player_t target = game_server->map->players[minion->target_id];
            unsigned int target_x;
            unsigned int target_y;

            pix_to_map(
                (int)target.pos.x, (int)target.pos.y,
                (int*)&(target_x), (int*)&(target_y)
            );
            if (!(target_x == minion->pos.x && target_y == minion->pos.y)) {
                TAckMinionUpdatePacket *p_mu = New_TAckMinionUpdatePacket(NULL);

                move_to_target(minion, target);

                p_mu->minion_pos = minion->pos;
                game_server->server->Send_Broadcast(
                    game_server->server,
                    packet_to_message((TPacket*)p_mu, 1)
                );
            }
        }
        minion->last_move_time = current_time;
    }
    // Heal
    if (current_time > minion->last_heal_time + minion->heal_speed) {
        minion->last_heal_time = current_time;
        if (minion->target_id != -1) {
            player_t *target = &(game_server->map->players[minion->target_id]);
            unsigned int target_x;
            unsigned int target_y;

            pix_to_map(
                (int)target->pos.x, (int)target->pos.y,
                (int*)&(target_x), (int*)&(target_y)
            );
            if (target_x == minion->pos.x && target_y == minion->pos.y) {
                TAckPlayerUpdatePacket *p_pu = New_TAckPlayerUpdatePacket(NULL);

                target->specs.life += 10;
                if (target->specs.life > PLAYER_MAX_LIFE)
                    target->specs.life = PLAYER_MAX_LIFE;
                p_pu->player = *target;
                game_server->server->Send_Broadcast(
                    game_server->server,
                    packet_to_message((TPacket*)p_pu, 1)
                );
            }
        }
    }
}

int get_nearest_player(minion_t minion, player_t *players)
{
    unsigned int i;
    int nearest_distance = 9999;
    int nearest_player = -1;

    if (!players) return (-1);
    for (i = 0; i < MAX_PLAYERS; i++) {
        if (players[i].connected && players[i].specs.life > 0) {
            pos_t pos_player;
            int distance;

            pix_to_map(
                (int)players[i].pos.x, (int)players[i].pos.y,
                (int*)&(pos_player.x), (int*)&(pos_player.y)
            );
            distance = distance_manhattan(minion.pos, pos_player);
            if (distance < nearest_distance) {
                nearest_distance = distance;
                nearest_player = i;
            }
            else if (distance == nearest_distance && rand_int(1) == 0) {
                nearest_player = i;
            }
        }
    }
    return (nearest_player);
}

void move_to_target(minion_t *minion, player_t player)
{
    graph_t *graph = create_graph(MAP_WIDTH, MAP_HEIGHT);
    int res_astar;
    vertice_t *minion_vert = NULL;
    vertice_t *player_vert = NULL;
    unsigned int player_x;
    unsigned int player_y;

    if (!graph) return;
    init_vertices(graph);

    pix_to_map(
        (int)player.pos.x, (int)player.pos.y,
        (int*)&(player_x), (int*)&(player_y)
    );

    minion_vert = graph->vertices[minion->pos.y][minion->pos.x];
    player_vert = graph->vertices[player_y][player_x];

    res_astar = astar_search(graph, node_cost, minion_vert, player_vert);

    if (res_astar) {
        vertice_t *path = player_vert;

        while (path->predecessor != minion_vert) {
            path = path->predecessor;
        }
        if (path->y < minion->pos.y)
            minion->pos.y--;
        if (path->y > minion->pos.y)
            minion->pos.y++;
        if (path->x < minion->pos.x)
            minion->pos.x--;
        if (path->x > minion->pos.x)
            minion->pos.x++;
    }
    free_graph(graph);
}

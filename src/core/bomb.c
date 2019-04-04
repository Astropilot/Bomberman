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
#include <stdio.h>

#include "core/bomb.h"
#include "core/map.h"
#include "core/minion.h"
#include "main.h"
#include "core/utils.h"
#include "network/server.h"
#include "network/packets/packet.h"
#include "network/packets/packet_ack_bombexplode.h"
#include "network/packets/packet_ack_playerupdate.h"
#include "network/packets/packet_ack_minionupdate.h"

static void logic_bomb_classic(TMap *map, bomb_t *bomb, TServer *server);

static void (*bombs_logic[])(TMap*, bomb_t*, TServer*) = {
    [CLASSIC] = logic_bomb_classic
};

void add_bomb(bomb_node_t **bombs_head, bomb_t *bomb)
{
    if (!bombs_head || !bomb) return;

    if (!*(bombs_head)) {
        bomb_node_t *bomb_node = malloc(sizeof(bomb_node_t));

        if (bomb_node) {
            bomb_node->bomb = bomb;
            bomb_node->next = NULL;
            *(bombs_head) = bomb_node;
        }
    } else {
        bomb_node_t *current = *(bombs_head);

        while (current->next != NULL)
            current = current->next;
        current->next = malloc(sizeof(bomb_node_t));
        if (current->next) {
            current->next->bomb = bomb;
            current->next->next = NULL;
        }
    }
}

void remove_bomb(bomb_node_t **bombs_head, bomb_t *bomb)
{
    if (!bombs_head || !bomb) return;

    bomb_node_t *current = *bombs_head;
    bomb_node_t *previous = NULL;

    while (current != NULL) {
        if (current->bomb == bomb) {
            if (!previous)
                *bombs_head = current->next;
            else
                previous->next = current->next;
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void do_bomb_logic(TMap *map, bomb_t *bomb, TServer *server)
{
    (*bombs_logic[bomb->type])(map, bomb, server);
}

static void logic_bomb_classic(TMap *map, bomb_t *bomb, TServer *server)
{
    player_t *player = &(map->players[bomb->owner_id]);
    TAckBombExplodePacket *packet = New_TAckBombExplodePacket(NULL);
    TAckPlayerUpdatePacket *p_ownerupdate = New_TAckPlayerUpdatePacket(NULL);
    unsigned int y, x, i;
    unsigned int bomb_start_x, bomb_start_y;
    unsigned int bomb_end_x, bomb_end_y;
    unsigned int max_blocs;
    bomb_node_t *node_bomb = map->bombs_head;

    player->specs.bombs_left++;
    packet->bomb = *bomb;

    bomb_start_x = ((int)bomb->bomb_pos.x - (int)bomb->range >= 0) ? bomb->bomb_pos.x - bomb->range : 0;
    bomb_start_y = ((int)bomb->bomb_pos.y - (int)bomb->range >= 0) ? bomb->bomb_pos.y - bomb->range : 0;
    bomb_end_x = ((int)bomb->bomb_pos.x + (int)bomb->range < MAP_WIDTH) ? bomb->bomb_pos.x + bomb->range : MAP_WIDTH - 1;
    bomb_end_y = ((int)bomb->bomb_pos.y + (int)bomb->range < MAP_HEIGHT) ? bomb->bomb_pos.y + bomb->range: MAP_HEIGHT - 1;

    /*
     * Reduction of the explosion radius if obstacles are present.
     */
    for (x = bomb_start_x; x <= bomb_end_x; x++) {
        object_type_t obj = map->block_map[bomb->bomb_pos.y][x];
        if (obj == WALL && x < bomb->bomb_pos.x)
            bomb_start_x = x + 1;
        if (obj == WALL && x > bomb->bomb_pos.x)
            bomb_end_x = x - 1;
        if (obj == BREAKABLE_WALL && x < bomb->bomb_pos.x)
            bomb_start_x = x;
        if (obj == BREAKABLE_WALL && x > bomb->bomb_pos.x)
            bomb_end_x = x;
    }
    for (y = bomb_start_y; y <= bomb_end_y; y++) {
        object_type_t obj = map->block_map[y][bomb->bomb_pos.x];
        if (obj == WALL && y < bomb->bomb_pos.y)
            bomb_start_y = y + 1;
        if (obj == WALL && y > bomb->bomb_pos.y)
            bomb_end_y = y - 1;
        if (obj == BREAKABLE_WALL && y < bomb->bomb_pos.y)
            bomb_start_y = y;
        if (obj == BREAKABLE_WALL && y > bomb->bomb_pos.y)
            bomb_end_y = y;
    }

    max_blocs = (bomb_end_x - bomb_start_x + 1) * (bomb_end_y - bomb_start_y + 1);
    packet->destroyed_walls = malloc(sizeof(pos_t) * max_blocs);
    packet->flames_blocks = malloc(sizeof(pos_t) * max_blocs);
    packet->extra_blocks = malloc(sizeof(object_t) * max_blocs);
    packet->destroyed_count = 0;
    packet->flames_count = 0;
    packet->extra_count = 0;
    /*
     * Addition of destroyed walls and generated flames.
     */
    for (y = bomb_start_y; y <= bomb_end_y; y++) {
        for (x = bomb_start_x; x <= bomb_end_x; x++) {
            if (x == bomb->bomb_pos.x || y == bomb->bomb_pos.y) {
                pos_t pos = {x, y};
                if (map->block_map[y][x] == BREAKABLE_WALL) {
                    map->block_map[y][x] = NOTHING;
                    if (rand_int(100) <= CHANCE_EXTRA) {
                        object_type_t extra = rand_range_int(BONUS_RANGE, MALUS_SPEED);
                        object_t obj = {extra, {x, y}};

                        map->block_map[y][x] = extra;
                        packet->extra_blocks[packet->extra_count] = obj;
                        packet->extra_count++;
                    }

                    packet->destroyed_walls[packet->destroyed_count] = pos;
                    packet->destroyed_count++;
                } else if (map->block_map[y][x] == NOTHING) {
                    if (!(x == bomb->bomb_pos.x && y == bomb->bomb_pos.y)) {
                        packet->flames_blocks[packet->flames_count] = pos;
                        packet->flames_count++;
                    }
                }
            }
        }
    }

    /*
     * Application of damage to players within the bomb's range.
     */
    for (i = 0; i < map->max_players; i++) {
        if (map->players[i].connected == 1 && map->players[i].specs.life > 0) {
            int player_y, player_x;
            pos_t player_pos = map->players[i].pos;

            pix_to_map((int)player_pos.x, (int)player_pos.y, &player_x, &player_y);
            if ( (player_x >= (int)bomb_start_x && player_x <= (int)bomb_end_x && player_y == (int)bomb->bomb_pos.y)
                ||
                (player_y >= (int)bomb_start_y && player_y <= (int)bomb_end_y && player_x == (int)bomb->bomb_pos.x) ) {
                    TAckPlayerUpdatePacket *p_pu = New_TAckPlayerUpdatePacket(NULL);

                    map->players[i].specs.life = ((int)map->players[i].specs.life - 40 < 0) ? 0 : map->players[i].specs.life - 40;
                    p_pu->player = map->players[i];
                    server->Send_Broadcast(server, packet_to_message((TPacket*)p_pu, 1));

                    if (map->minion->target_id == (int)map->players[i].p_id) {
                        TAckMinionUpdatePacket *p_mu = New_TAckMinionUpdatePacket(NULL);

                        init_minion(map->minion);
                        p_mu->minion_pos = map->minion->pos;
                        server->Send_Broadcast(server, packet_to_message((TPacket*)p_mu, 1));
                    }
            }
        }
    }

    /*
     * Explosion of other bombs within the bomb's range.
     */
    while (node_bomb != NULL) {
        pos_t bomb_pos = node_bomb->bomb->bomb_pos;
        if ( (bomb_pos.x >= bomb_start_x && bomb_pos.x <= bomb_end_x && bomb_pos.y == bomb->bomb_pos.y)
            ||
            (bomb_pos.y >= bomb_start_y && bomb_pos.y <= bomb_end_y && bomb_pos.x == bomb->bomb_pos.x) ) {
                node_bomb->bomb->time_explode = 0;
        }
        node_bomb = node_bomb->next;
    }

    p_ownerupdate->player = map->players[bomb->owner_id];
    server->Send_Broadcast(server, packet_to_message((TPacket*)packet, 1));
    server->Send_Broadcast(server, packet_to_message((TPacket*)p_ownerupdate, 1));
}

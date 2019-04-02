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
#include <string.h>

#include "main.h"
#include "core/player.h"
#include "core/utils.h"

unsigned int next_id(player_t *players)
{
    unsigned int i;

    if (!players) return (MAX_PLAYERS + 1);
    for (i = 0; i < MAX_PLAYERS; i++) {
        if (!players[i].connected)
            return (i);
    }
    return (MAX_PLAYERS + 1);
}

void init_player(player_t *player, int id, const char *username)
{
    if (!player || !username) return;

    player->connected = 1;
    player->username = strdup(username);
    player->p_id = (unsigned int)id;

    player->specs.life = PLAYER_MAX_LIFE;
    player->specs.move_speed = 400;
    player->specs.bombs_capacity = 1;
    player->specs.bombs_left = player->specs.bombs_capacity;
    player->specs.bombs_range = 1;

    player->last_move_time = 0;
    switch (id) {
        case 0:
            map_to_pix(0, 0, (int*)&(player->pos.x), (int*)&(player->pos.y));
            player->direction = (unsigned int)EAST;
            break;
        case 1:
            map_to_pix(MAP_WIDTH - 1, 0, (int*)&(player->pos.x), (int*)&(player->pos.y));
            player->direction = (unsigned int)WEST;
            break;
        case 2:
            map_to_pix(0, MAP_HEIGHT - 1, (int*)&(player->pos.x), (int*)&(player->pos.y));
            player->direction = (unsigned int)EAST;
            break;
        case 3:
            map_to_pix(MAP_WIDTH - 1, MAP_HEIGHT - 1, (int*)&(player->pos.x), (int*)&(player->pos.y));
            player->direction = (unsigned int)WEST;
            break;
    }
}

unsigned int alive_players(player_t *players)
{
    unsigned int i;
    unsigned int alive_count = 0;

    if (!players) return (0);
    for (i = 0; i < MAX_PLAYERS; i++) {
        if (players[i].connected && players[i].specs.life > 0)
            alive_count++;
    }
    return (alive_count);
}

player_t *get_first_alive_player(player_t *players)
{
    unsigned int i;

    if (!players) return (NULL);
    for (i = 0; i < MAX_PLAYERS; i++) {
        if (players[i].connected && players[i].specs.life > 0)
            return &(players[i]);
    }
    return (NULL);
}

void reset_player(player_t *player)
{
    if (player) {
        player->connected = 0;
        free(player->username);
        player->username = NULL;
    }
}

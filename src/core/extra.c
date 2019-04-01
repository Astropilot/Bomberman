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
#include "core/extra.h"
#include "core/map.h"
#include "core/player.h"

static void logic_bonus_range(player_t *player);
static void logic_malus_range(player_t *player);
static void logic_bonus_capacity(player_t *player);
static void logic_malus_capacity(player_t *player);
static void logic_bonus_speed(player_t *player);
static void logic_malus_speed(player_t *player);

static void (*extras_logic[])(player_t*) = {
    [BONUS_RANGE] = logic_bonus_range,
    [MALUS_RANGE] = logic_malus_range,
    [BONUS_CAPACITY] = logic_bonus_capacity,
    [MALUS_CAPACITY] = logic_malus_capacity,
    [BONUS_SPEED] = logic_bonus_speed,
    [MALUS_SPEED] = logic_malus_speed
};

static char *extra_paths[] = {
    [BONUS_RANGE] = MAP_PATH "bomb_range_bonus%02d.png",
    [MALUS_RANGE] = MAP_PATH "bomb_range_malus%02d.png",
    [BONUS_CAPACITY] = MAP_PATH "bomb_amount_bonus%02d.png",
    [MALUS_CAPACITY] = MAP_PATH "bomb_amount_malus%02d.png",
    [BONUS_SPEED] = MAP_PATH "speed_bonus%02d.png",
    [MALUS_SPEED] = MAP_PATH "speed_malus%02d.png"
};

unsigned int do_extra_logic(player_t *player, object_type_t extra_type)
{
    if (!player || extra_type < BONUS_RANGE || extra_type > MALUS_SPEED) return (0);

    (*extras_logic[extra_type])(player);
    return (1);
}

char *extra_to_resource(object_type_t extra_type)
{
    return (extra_paths[extra_type]);
}

static void logic_bonus_range(player_t *player)
{
    player->specs.bombs_range++;
}

static void logic_malus_range(player_t *player)
{
    if (player->specs.bombs_range > 1)
        player->specs.bombs_range--;
}

static void logic_bonus_capacity(player_t *player)
{
    player->specs.bombs_capacity++;
    player->specs.bombs_left++;
}

static void logic_malus_capacity(player_t *player)
{
    if (player->specs.bombs_capacity > 1) {
        player->specs.bombs_capacity--;
        player->specs.bombs_left--;
    }
}

static void logic_bonus_speed(player_t *player)
{
    if (player->specs.move_speed > 200)
        player->specs.move_speed -= 50;
}

static void logic_malus_speed(player_t *player)
{
    if (player->specs.move_speed < 400)
        player->specs.move_speed += 50;
}

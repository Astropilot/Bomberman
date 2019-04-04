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

/**
 * @file core/minion.h
 * @brief Header file of the minion logic.
 *
 * All methods for minion logic are here.
 *
 */

#ifndef CORE_MINION_H_
#define CORE_MINION_H_

#include "core/player.h"
#include "core/utils.h"
#include "network/game/server.h"

/**
 * @brief structure representing a minion.
 *
 * minion_t is a structure representing a minion.
 */
typedef struct minion_t {

    pos_t pos;                          /*!< The position of the minion on the map. */
    unsigned int heal;
    unsigned int heal_speed;
    int target_id;
    unsigned int move_speed;
    unsigned int last_move_time;        /*!< Internal variable for speed control. */
    unsigned int last_heal_time;        /*!< Internal variable for speed control. */

} minion_t ;

void init_minion(minion_t *minion);

void minion_handle_logic(minion_t *minion, unsigned int current_time, TGameServer *game_server);

int get_nearest_player(minion_t minion, player_t *players);

void move_to_target(minion_t *minion, player_t player);

#endif

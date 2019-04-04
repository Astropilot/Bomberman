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
    unsigned int heal;                  /*!< The heal given. */
    unsigned int heal_speed;            /*!< The delay between each heal. */
    int target_id;                      /*!< The ID of the player the minion is following. */
    unsigned int move_speed;            /*!< The speed of the minion. */
    unsigned int last_move_time;        /*!< Internal variable for speed control. */
    unsigned int last_heal_time;        /*!< Internal variable for speed control. */

} minion_t ;

/**
 * @fn void init_minion(minion_t *minion)
 * @brief Initializes a minion with default values.
 *
 * @param minion A pointer to the minion to initialize.
 */
void init_minion(minion_t *minion);

/**
 * @fn void minion_handle_logic(minion_t *minion, unsigned int current_time, TGameServer *game_server)
 * @brief Handle the logic of the minion, including movement and heal actions.
 *
 * @param minion A pointer to the minion.
 * @param current_time The current time in milliseconds.
 * @param game_server The game server instance.
 */
void minion_handle_logic(minion_t *minion, unsigned int current_time, TGameServer *game_server);

/**
 * @fn int get_nearest_player(minion_t minion, player_t *players)
 * @brief Returns the player closest to the minion.
 *
 * @param minion A pointer to the minion.
 * @param players The list of players in the game.
 * @return The ID of the nearest player, -1 if no player found.
 */
int get_nearest_player(minion_t minion, player_t *players);

/**
 * @fn void move_to_target(minion_t *minion, player_t player)
 * @brief Moves the minion towards the given player.
 *
 * @param minion A pointer to the minion.
 * @param player The player to follow.
 */
void move_to_target(minion_t *minion, player_t player);

#endif

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
 * @file core/player.h
 * @brief Header file of the players logic.
 *
 * All methods for players logic are here.
 *
 */

#ifndef CORE_PLAYER_H_
#define CORE_PLAYER_H_

#include "core/utils.h"

/**
 * @brief Constants of the directions.
 *
 * direction_t is a series of predefined constants for the different
 * direction of a player.
 */
typedef enum direction_t {
    NORTH,                              /*!< The North direction. */
    WEST,                               /*!< The West direction. */
    EAST,                               /*!< The East direction. */
    SOUTH                               /*!< The South direction. */
} direction_t ;

/**
 * @brief structure representing the specificities of a player.
 *
 * player_specs_t is a structure representing the specificities of a player.
 */
typedef struct player_specs_t {

    unsigned int life;                  /*!< The life of the player. */
    unsigned int move_speed;            /*!< The speed of the player. */
    unsigned int bombs_capacity;        /*!< The capacity of the player for bombs. */
    unsigned int bombs_left;            /*!< The number of bombs left that the player can place. */
    unsigned int bombs_range;           /*!< The range of the new bombs placed. */

} player_specs_t ;

/**
 * @brief structure representing a player.
 *
 * player_t is a structure representing a player.
 */
typedef struct player_t {

    unsigned int connected;             /*!< A boolean to know if the player is connected. */
    char *username;                     /*!< The username of the player. */
    unsigned int p_id;                  /*!< The unique ID of the player.*/
    pos_t pos;                          /*!< The position of the player on the map. */
    unsigned int direction;             /*!< The actual direction where the player look at. */
    player_specs_t specs;               /*!< The specificities of the player. */
    unsigned int last_move_time;        /*!< Internal variable for speed control. */

} player_t ;

/**
 * @fn unsigned int next_id(player_t *players)
 * @brief Get the smallest possible ID for a new player.
 *
 * @param players The list of all players.
 * @return Return a free ID for a new player.
 */
unsigned int next_id(player_t *players);

/**
 * @fn void init_player(player_t *player, int id, const char *username)
 * @brief Initializes a new player from his new ID and username.
 *
 * @param player A pointer to the new player.
 * @param id The ID of the new player. Mostly get from next_id/1 function.
 * @param username The username of the new player.
 */
void init_player(player_t *player, int id, const char *username);

/**
 * @fn unsigned int alive_players(player_t *players)
 * @brief Return the number of players alive in a player list.
 *
 * @param players The list of players.
 * @return Return the number of players alive.
 */
unsigned int alive_players(player_t *players);

/**
 * @fn player_t *get_first_alive_player(player_t *players)
 * @brief Return the first player alive found in a player list.
 *
 * @param players The list of players.
 * @return Return the first player alive.
 */
player_t *get_first_alive_player(player_t *players);

/**
 * @fn void reset_player(player_t *player)
 * @brief Reset a player.
 *
 * @param player A pointer to the player to reset.
 */
void reset_player(player_t *player);

#endif

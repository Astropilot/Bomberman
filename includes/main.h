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
 * @file main.h
 * @brief The Bomberman game.
 *
 * This file define some Game et Ui constants.
 *
 */

#ifndef MAIN_H_
#define MAIN_H_

/***************************  UI CONSTS ***************************/

#define WIN_WIDTH 1280                      /*!< The width of the window. */
#define WIN_HEIGHT 720                      /*!< The height of the window. */

/***************************  GAME CONSTS *************************/

#define GAME_VERSION "1.0.0"                /*!< The game version. */

// MAX_PLAYERS and MIN_PLAYERS need to be lower or equal to 4.
#define MAX_PLAYERS 4                       /*!< The maximum number of players allowed in a game. */
#define MIN_PLAYERS 2                       /*!< The minimum number of players to start a game. */

#define MAP_START_PIX_X 368                 /*!< The x-axis coordinate in pixels of the top-left coin of the map. */
#define MAP_START_PIX_Y 159                 /*!< The y-axis coordinate in pixels of the top-left coin of the map. */

#define MAP_WIDTH 17                        /*!< The map width.*/
#define MAP_HEIGHT 15                       /*!< The map height.*/
#define MAP_BLOCK_SIZE 32                   /*!< The size in pixels of a block.*/

#define BLOCK_INFO_WIDTH 290                /*!< The width in pixels of a information player block.*/
#define BLOCK_INFO_HEIGHT 95                /*!< The height in pixels of a information player block.*/

#define CHANCE_BREAKABLE_WALL 20            /*!< Percentage chance of breakable walls appearing. */
#define CHANCE_EXTRA 60                     /*!< Percentage chance of extras appearing (bonus / malus). */

#define PLAYER_MAX_LIFE 100                 /*!< The maximum life value for a player. */

#define IS_DEBUG 0                          /*!< Define if the game is in debug mode or not. */

#define RES_PATH "images/"                  /*!< The path for the sprite resources. */
#define FONT_PATH "fonts/"                  /*!< The path for the font resources. */
#define CHAR_PATH RES_PATH "character/"     /*!< The path for the character specific resources. */
#define MINION_PATH RES_PATH "minion/"      /*!< The path for the minion specific resources. */
#define MAP_PATH RES_PATH "map/"            /*!< The path for the map specific resources. */
#define BOMB_PATH RES_PATH "bomb/"          /*!< The path for the bomb specific resources. */

/**
 * @brief A structure representing differents args for lobby and game frames.
 *
 * lobby_args_t is structure representing differents args for
 * lobby and game frames.
 */
typedef struct lobby_args_t {
    char *username;             /*!< The username of the player. */
    char *server_ip;            /*!< The IP of the hosted game. */
    int port;                   /*!< The port of the hosted game. */
} lobby_args_t ;

#endif

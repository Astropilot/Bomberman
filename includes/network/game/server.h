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
 * @file network/game/server.h
 * @brief Header file of the TGameServer class.
 *
 * The TGameServer object allow you to create a game server.
 *
 */

#ifndef NETWORK_SERVER_H_
#define NETWORK_SERVER_H_

#include <SDL2/SDL_thread.h>

#include "main.h"
#include "network/network.h"
#include "core/map.h"

/**
 * @brief An class representing the game logic from server side.
 *
 * TGameServer is a class representing the game logic from server side.
 */
typedef struct TGameServer {

    void(*Start)(struct TGameServer*, int);         /*!< Start the server on the given port. */

    void(*Stop)(struct TGameServer*);               /*!< Stop the server. */

    void(*Free)(struct TGameServer*);               /*!< Free (ressources) method. */

    TServer *server;                                /*!< The network server. */
    SDL_Thread *server_thread;                      /*!< Internal thread handle for server loop. */
    unsigned int is_listenning;                     /*!< A boolean to know if the server is listenning. */
    int nb_players;                                 /*!< The actual number of players connected. */
    int ready_players;                              /*!< The actual number of players ready to play. */
    TMap *map;                                      /*!< The game map. */
    unsigned int game_started;                      /*!< The boolean to know if the game started. */
    game_rules_t rules;                             /*!< The rules of the game. */
    TClient **player_socks;                         /*!< A array containing the network instances of the players. */

} TGameServer ;

/**
 * @brief The constructor for create a TGameServer object.
 *
 * @param rules The rules of the party.
 * @return A memory allocated object of the game server.
 */
TGameServer* New_TGameServer(game_rules_t rules);

/**
 * @brief Start the network server on the given port with a maximum clients authorized.
 *
 * @param this A pointer to the game server object.
 * @param port The port on which the server will listen.
 *
 * You do not have to call this method directly. You must use the
 * Start method of the TGameServer structure like this:
 * my_gameserver->Start(my_gameserver, 3306, 4);
 */
void TGameServer_Start(TGameServer *this, int port);

/**
 * @brief Stop the network server.
 *
 * @param this A pointer to the game server object.
 *
 * You do not have to call this method directly. You must use the
 * Stop method of the TGameServer structure like this:
 * my_gameserver->Stop(my_gameserver);
 */
void TGameServer_Stop(TGameServer *this);

/**
 * @brief Method to free all ressources take by the game server.
 *
 * @param this A pointer to the game server object to free.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TGameServer structure like this:
 * my_gameserver->Free(my_gameserver);
 */
void TGameServer_New_Free(TGameServer *this);

#endif

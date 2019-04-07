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
 * @file network/game/client.h
 * @brief Header file of the TGameClient class.
 *
 * The TGameClient object allow you to create a game client.
 *
 */

#ifndef NETWORK_CLIENT_H_
#define NETWORK_CLIENT_H_

#include "glib.h"
#include "core/player.h"
#include "network/network.h"
#include "network/game/server.h"

/**
 * @brief An class representing the game logic from client side.
 *
 * TGameClient is a class representing the game logic from client side.
 */
typedef struct TGameClient {

    TScene*(*Register_Scene)(struct TGameClient*, TScene*);     /*!< Method for register the UI scene used for the game. */

    void(*Ready)(struct TGameClient*);                          /*!< Method for say to the server that the player is ready to process the game. */

    void(*Move)(struct TGameClient*, direction_t);              /*!< Method for say to the server that the player want to move. */

    void(*Place_Bomb)(struct TGameClient*);                     /*!< Method for say to the server that the player want to drop a bomb. */

    void(*Handle_Messages)(struct TGameClient*);                /*!< Method for handle the message sended by the server. */

    void(*Leave_Game)(struct TGameClient*);                     /*!< Method for say to the server that the player left the game. */

    void(*Free)(struct TGameClient*);                           /*!< Free (ressources) method. */

    TClient *client;                                            /*!< The network client. */
    TGameServer *gameserver;                                    /*!< The game server object if the client is the game owner. */
    TScene *game_scene;                                         /*!< The UI scene corresponding to the game.*/
    unsigned int is_owner;                                      /*!< A boolean to know if the client is the game owner. */
    int player;                                                 /*!< The unique ID of the player. */
    unsigned int bomb_offset;                                   /*!< The latest bomb id dropped. */

} TGameClient ;

/**
 * @fn TGameClient* New_TGameClient()
 * @brief The constructor for create a TGameClient object.
 *
 * @return A memory allocated object of the game client.
 */
TGameClient* New_TGameClient();

/**
 * @fn TScene *TGameClient_Register_Scene(TGameClient *this, TScene *scene)
 * @brief Method for register the UI scene responsible for displaying the game.
 *
 * @param this A pointer to the game client object.
 * @param scene The UI scene responsible for displaying the game.
 * @return Returns the same pointer of the scene given.
 *
 * You do not have to call this method directly. You must use the
 * Register_Scene method of the TGameClient structure like this:
 * my_gameclient->Register_Scene(my_gameclient, my_scene);
 */
TScene *TGameClient_Register_Scene(TGameClient *this, TScene *scene);

/**
 * @fn void TGameClient_Ready(TGameClient *this)
 * @brief Method to inform the server that this client is ready to start the game.
 *
 * @param this A pointer to the game client object.
 *
 * You do not have to call this method directly. You must use the
 * Ready method of the TGameClient structure like this:
 * my_gameclient->Ready(my_gameclient);
 */
void TGameClient_Ready(TGameClient *this);

/**
 * @fn void TGameClient_Move(TGameClient *this, direction_t direction)
 * @brief Method to inform the server that this client want to move in a specific direction.
 *
 * @param this A pointer to the game client object.
 * @param direction The direction wanted by the player.
 *
 * You do not have to call this method directly. You must use the
 * Move method of the TGameClient structure like this:
 * my_gameclient->Move(my_gameclient, NORTH);
 */
void TGameClient_Move(TGameClient *this, direction_t direction);

/**
 * @fn void TGameClient_Place_Bomb(TGameClient *this)
 * @brief Method to inform the server that this client want to drop a bomb.
 *
 * @param this A pointer to the game client object.
 *
 * You do not have to call this method directly. You must use the
 * Place_Bomb method of the TGameClient structure like this:
 * my_gameclient->Place_Bomb(my_gameclient);
 */
void TGameClient_Place_Bomb(TGameClient *this);

/**
 * @fn void TGameClient_Handle_Messages(TGameClient *this)
 * @brief Method that handle the messages sended by the server.
 *
 * @param this A pointer to the game client object.
 *
 * You do not have to call this method directly. You must use the
 * Handle_Messages method of the TGameClient structure like this:
 * my_gameclient->Handle_Messages(my_gameclient);
 */
void TGameClient_Handle_Messages(TGameClient *this);

/**
 * @fn void TGameClient_Leave_Game(TGameClient *this)
 * @brief Method to inform the server that this client leave the game.
 *
 * @param this A pointer to the game client object.
 *
 * You do not have to call this method directly. You must use the
 * Leave_Game method of the TGameClient structure like this:
 * my_gameclient->Leave_Game(my_gameclient);
 */
void TGameClient_Leave_Game(TGameClient *this);

/**
 * @fn void TGameClient_New_Free(TGameClient *this)
 * @brief Method to free all ressources take by the game client.
 *
 * @param this A pointer to the game client object to free.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TGameClient structure like this:
 * my_gameclient->Free(my_gameclient);
 */
void TGameClient_New_Free(TGameClient *this);

#endif

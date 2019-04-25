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
 * @file network/game/lobby.h
 * @brief Header file of the TLobbyClient class.
 *
 * The TLobbyClient object allow you to create a lobby client.
 *
 */

#ifndef NETWORK_LOBBY_H_
#define NETWORK_LOBBY_H_

#include "glib.h"
#include "network/network.h"
#include "network/game/server.h"

/**
 * @brief An class representing the lobby logic from client side.
 *
 * TLobbyClient is a class representing the lobby logic from client side.
 */
typedef struct TLobbyClient {

    TScene*(*Register_Scene)(struct TLobbyClient*, TScene*);                /*!< Method for register the UI scene used for the lobby. */

    void(*Start_Server)(struct TLobbyClient*, int, game_rules_t);           /*!< Method for start the game server. */

    void(*Join_Lobby)(struct TLobbyClient*, const char*, const char*, int); /*!< Method for joining the lobby. */

    void(*Start_Game)(struct TLobbyClient*);                                /*!< Method called by the game owner to start the game. */

    void(*Handle_Messages)(struct TLobbyClient*);                           /*!< Method for handle the message sended by the server. */

    void(*Leave_Lobby)(struct TLobbyClient*);                               /*!< Method for say to the server that the player left the lobby. */

    void(*Free)(struct TLobbyClient*);                                      /*!< Free (ressources) method. */

    TClient *client;                /*!< The network client for sending messages to the server. */
    TGameServer *gameserver;        /*!< The game server object if the client is the game owner. */
    TScene *lobby_scene;            /*!< The UI scene corresponding to the lobby.*/
    unsigned int is_owner;          /*!< A boolean to know if the client is the game owner. */
    int player;                     /*!< The unique ID of the player. */
    unsigned int nb_players;        /*!< The actual number of players in the lobby. */
    game_rules_t rules;             /*!< The rules of the game. */

} TLobbyClient ;

/**
 * @brief The constructor for create a TLobbyClient object.
 *
 * @return A memory allocated object of the lobby client.
 */
TLobbyClient* New_TLobbyClient();

/**
 * @brief Method for register the UI scene responsible for displaying the lobby.
 *
 * @param this A pointer to the lobby client object.
 * @param scene The UI scene responsible for displaying the lobby.
 * @return Returns the same pointer of the scene given.
 *
 * You do not have to call this method directly. You must use the
 * Register_Scene method of the TLobbyClient structure like this:
 * my_lobbyclient->Register_Scene(my_lobbyclient, my_scene);
 */
TScene *TLobbyClient_Register_Scene(TLobbyClient *this, TScene *scene);

/**
 * @brief Method to create a new game server in background.
 *
 * @param this A pointer to the lobby client object.
 * @param port The port on which the server will listen.
 * @param rules The rules of the party.
 *
 * You do not have to call this method directly. You must use the
 * Start_Server method of the TLobbyClient structure like this:
 * my_lobbyclient->Start_Server(my_lobbyclient, 3306, my_rules);
 */
void TLobbyClient_Start_Server(TLobbyClient *this, int port, game_rules_t rules);

/**
 * @brief Method to join the lobby of a hosted game.
 *
 * @param this A pointer to the lobby client object.
 * @param username The username wanted by the client.
 * @param ip The IP (or hostname) of the game host.
 * @param port The port of the game host.
 *
 * You do not have to call this method directly. You must use the
 * Join_Lobby method of the TLobbyClient structure like this:
 * my_lobbyclient->Join_Lobby(my_lobbyclient, "MyPseudo", "127.0.0.1", 3306);
 */
void TLobbyClient_Join_Lobby(TLobbyClient *this, const char *username, const char *ip, int port);

/**
 * @brief Method to inform the server that the game owner want to start the game.
 *
 * @param this A pointer to the lobby client object.
 *
 * You do not have to call this method directly. You must use the
 * Start_Game method of the TLobbyClient structure like this:
 * my_lobbyclient->Start_Game(my_lobbyclient);
 */
void TLobbyClient_Start_Game(TLobbyClient *this);

/**
 * @brief Method that handle the messages sended by the server.
 *
 * @param this A pointer to the lobby client object.
 *
 * You do not have to call this method directly. You must use the
 * Handle_Messages method of the TLobbyClient structure like this:
 * my_lobbyclient->Handle_Messages(my_lobbyclient);
 */
void TLobbyClient_Handle_Messages(TLobbyClient *this);

/**
 * @brief Method to inform the server that this client leave the lobby.
 *
 * @param this A pointer to the lobby client object.
 *
 * You do not have to call this method directly. You must use the
 * Leave_Game method of the TLobbyClient structure like this:
 * my_lobbyclient->Leave_Game(my_lobbyclient);
 */
void TLobbyClient_Leave_Lobby(TLobbyClient *this);

/**
 * @brief Method to free all ressources take by the lobby client.
 *
 * @param this A pointer to the lobby client object to free.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TLobbyClient structure like this:
 * my_lobbyclient->Free(my_lobbyclient);
 */
void TLobbyClient_New_Free(TLobbyClient *this);

#endif

/*******************************************************************************
* PROJECT: gLib
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
 * @file network/server.h
 * @brief Header file of the server class of gLib.
 *
 * This class allows you to create a socket server with
 * high-level methods for manipulating clients.
 *
 */

#ifndef GLIB_SERVER_H_
#define GLIB_SERVER_H_

#include "sockets.h"
#include "client.h"
#include "message.h"

/**
 * @brief A linked list node for clients.
 *
 * TClient_Node is an linked list node for stock the clients.
 */
typedef struct TClient_Node {
    TClient *client;                    /*!< The client object. */
    struct TClient_Node *next;          /*!< A pointer to the next TClient_Node. */
} TClient_Node ;

/**
 * @brief Object oriented structure representing a server.
 *
 * TServer is an object that allows you to create a high-level socket server.
 */
typedef struct TServer {

    void(*Start_Listenning)(struct TServer*);               /*!< Start listening for new clients in an asynchronous way. */

    void(*Stop_Listenning)(struct TServer*);                /*!< Stop the asynchrone listening. */

    void(*Send_Broadcast)(struct TServer*, TMessage);       /*!< Send a message to all connected clients. */

    unsigned int(*CountClients)(struct TServer*);           /*!< Get the number of connected clients. */

    void(*Disconnect_Client)(struct TServer*, TClient*);    /*!< Disconnect a specific client. */

    void(*Free)(struct TServer*);                           /*!< Free (ressources) method. */

    /* Callbacks */

    void(*On_Connect)(struct TServer*, TClient*);           /*!< Callback called when a client arrive.*/

    void(*On_Message)(struct TServer*, TClient*, TMessage); /*!< Callback called when a message is receive. */

    SOCKET server_sock;                                     /*!< The socket used by the server.*/
    unsigned int is_listenning;                             /*!< An boolean to know if the server is listening for new clients. */
    unsigned int max_c;                                     /*!< The maximum number of clients allowed to connect to the server. */
    SDL_Thread *server_thread;                              /*!< The thread used for listening. */
    TClient_Node *clients_head;                             /*!< The list of connected clients. */

} TServer ;

/**
 * @brief The constructor for create a TServer object.
 *
 * @param port The port to listening.
 * @param max_c The maximum number of clients allowed to connect.
 * @return A memory allocated object of the server.
 */
TServer* New_TServer(unsigned short int port, unsigned int max_c);

/**
 * @brief Start listening for new clients. (Asynchrone)
 *
 * @param this A pointer to the server object.
 *
 * You do not have to call this method directly. You must use the
 * Start_Listenning method of the TServer structure like this:
 * my_server->Start_Listenning(my_server);
 */
void TServer_Start_Listenning(TServer *this);

/**
 * @brief Stop listening for new clients.
 *
 * @param this A pointer to the server object.
 *
 * You do not have to call this method directly. You must use the
 * Stop_Listenning method of the TServer structure like this:
 * my_server->Stop_Listenning(my_server);
 */
void TServer_Stop_Listenning(TServer *this);

/**
 * @brief Send a message to all connected clients.
 *
 * @param this A pointer to the server object.
 * @param message The message to send.
 *
 * You do not have to call this method directly. You must use the
 * Send_Broadcast method of the TServer structure like this:
 * my_server->Send_Broadcast(my_server, message);
 */
void TServer_Send_Broadcast(TServer *this, TMessage message);

/**
 * @brief Return the number of connected clients.
 *
 * @param this A pointer to the server object.
 * @return The number of connected clients.
 *
 * You do not have to call this method directly. You must use the
 * CountClients method of the TServer structure like this:
 * my_server->CountClients(my_server);
 */
unsigned int TServer_CountClients(TServer *this);

/**
 * @brief Disconnect a client and remove it from the server.
 *
 * @param this A pointer to the server object.
 * @param client The client to disconnect.
 *
 * You do not have to call this method directly. You must use the
 * Disconnect_Client method of the TServer structure like this:
 * my_server->Disconnect_Client(my_server, my_client);
 */
void TServer_Disconnect_Client(TServer *this, TClient *client);

/**
 * @brief Method to free all ressources take by the server and clients.
 *
 * @param this A pointer to the server object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TServer structure like this:
 * my_server->Free(my_server);
 */
void TServer_New_Free(TServer *this);

#endif

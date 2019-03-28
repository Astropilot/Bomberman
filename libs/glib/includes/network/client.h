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
 * @file client.h
 * @brief Header file of the client class of gLib.
 *
 * This class allows you to create a socket client with
 * high-level methods for sending and receving data.
 *
 */

#ifndef GLIB_CLIENT_H_
#define GLIB_CLIENT_H_

#include <SDL2/SDL_thread.h>

#include "sockets.h"
#include "message.h"

typedef struct TServer TServer;

/**
 * @brief Object oriented structure representing a client.
 *
 * TClient is an object that allows you to create a high-level socket client.
 */
typedef struct TClient {

    int(*Connect)(struct TClient*, const char*, unsigned short int); /*!< Method to connect to a server. */

    int(*Send)(struct TClient*, TMessage);                           /*!< Method to send a TMessage. */

    int(*Recv)(struct TClient*, TMessage*);                          /*!< Method to receive a TMessage. */

    void(*Start_Recv)(struct TClient*, TServer*);                    /*!< Method to start an asynchrone receving. */

    void(*Stop_Recv)(struct TClient*);                               /*!< Method to stop the asynchrone receving. */

    void(*Disconnect)(struct TClient*);                              /*!< Method to close the connection. */

    void(*Free)(struct TClient*);                                    /*!< Free (ressources) method. */

    /* Callbacks */

    void(*On_Message)(struct TClient*, TMessage);                    /*!< Callback when a TMessage has been receive. */

    void(*Server_On_Message)(struct TClient*, TServer*, TMessage);   /*!< Same callback as On_Message but for TServer purpose. */

    SOCKET sock;                            /*!< The client socket */
    unsigned int is_receving;               /*!< An boolean to know if an asynchrone receving has been started. */
    unsigned int is_connected;              /*!< An boolean to know if the socket is connected. */
    SDL_Thread *client_thread;              /*!< The thread for asynchronous receving. */
    TServer* server;                        /*!< Internal reference to a TServer if this client came from an server. */

} TClient ;

/**
 * @fn TClient *New_TClient(void)
 * @brief The constructor for create a TClient object.
 *
 * @return A memory allocated object of the client.
 */
TClient *New_TClient(void);

/**
 * @fn int TClient_Connect(TClient *this, const char *addr, unsigned short int port)
 * @brief Method to connect to a server.
 *
 * @param this A pointer to the client object.
 * @param addr The address of the server, can be an IP or an domain.
 * @param port The port of the server.
 * @return A 0 value if connection is a success, -1 otherwise.
 *
 * You do not have to call this method directly. You must use the
 * Connect method of the TClient structure like this:
 * my_client->Connect(my_client, "127.0.0.1", 8888);
 */
int TClient_Connect(TClient *this, const char *addr, unsigned short int port);

/**
 * @fn int TClient_Send(TClient *this, TMessage message)
 * @brief Method to send a message to the server.
 *
 * @param this A pointer to the client object.
 * @param message The message to send.
 * @return A 0 value if send is a success, -1 otherwise.
 *
 * You do not have to call this method directly. You must use the
 * Send method of the TClient structure like this:
 * my_client->Send(my_client, my_message);
 */
int TClient_Send(TClient *this, TMessage message);

/**
 * @fn int TClient_Recv(TClient *this, TMessage *message)
 * @brief Method to receive a message from the server. This method is non-blocking.
 *
 * @param this A pointer to the client object.
 * @param message An pointer to message object to write the received one.
 * @return The message length if the receving is a success.
 * Otherwise -1 if error or EWOULDBLOCK/EAGAIN if not messsage available.
 *
 * You do not have to call this method directly. You must use the
 * Recv method of the TClient structure like this:
 * my_client->Recv(my_client, &my_message);
 */
int TClient_Recv(TClient *this, TMessage *message);

/**
 * @fn void TClient_Start_Recv(TClient *this, TServer *server)
 * @brief Method to start listening for message in an asynchronous way.
 *
 * @param this A pointer to the client object.
 * @param server You must put NULL here. This parameter is used by TServer only.
 *
 * You do not have to call this method directly. You must use the
 * Start_Recv method of the TClient structure like this:
 * my_client->Start_Recv(my_client, NULL);
 */
void TClient_Start_Recv(TClient *this, TServer *server);

/**
 * @fn void TClient_Stop_Recv(TClient *this)
 * @brief Method to stop listening for message in an asynchronous way.
 *
 * @param this A pointer to the client object.
 *
 * You do not have to call this method directly. You must use the
 * Stop_Recv method of the TClient structure like this:
 * my_client->Stop_Recv(my_client);
 */
void TClient_Stop_Recv(TClient *this);

/**
 * @fn void TClient_Disconnect(TClient *this)
 * @brief Method to disconnect from server.
 *
 * @param this A pointer to the client object.
 *
 * You do not have to call this method directly. You must use the
 * Disconnect method of the TClient structure like this:
 * my_client->Disconnect(my_client);
 */
void TClient_Disconnect(TClient *this);

/**
 * @fn void TClient_New_Free(TClient *this)
 * @brief Method to free all ressources take by the client.
 *
 * @param this A pointer to the client object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TClient structure like this:
 * my_client->Free(my_client);
 */
void TClient_New_Free(TClient *this);

#endif

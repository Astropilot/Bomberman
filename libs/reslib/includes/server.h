/*
** ETNA PROJECT, 05/02/2019 by martin_h, hamide_a, despla_g, weber_w
** resLib
** File description:
**      Wrapper around the socket API.
*/

/**
 * @file server.h
 * @brief Header file of the server class of ResLib.
 * @author Yohann.M, Gauthier.D, Aziz.H, William.W
 * @version 1.0
 * @date 28 janvier 2019
 *
 * This class allows you to create a socket server with
 * high-level methods for manipulating clients.
 *
 */

#ifndef RESLIB_SERVER_H_
#define RESLIB_SERVER_H_

#include "sockets.h"
#include "client.h"
#include "message.h"

/**
 * @struct TClient_Node
 * @brief A linked list node for clients socket.
 *
 * TClient_Node is an linked list node for stock the clients socket.
 */
typedef struct {
    SOCKET sock;
    struct TClient_Node *next;
} TClient_Node ;

/**
 * @struct TServer
 * @brief Object oriented structure representing a server.
 *
 * TServer is an object that allows you to create a high-level socket server.
 */
typedef struct {

    void(*Start_Listenning)(struct TServer*);               /*!< Start listening for new clients in an asynchronous way. */

    void(*Stop_Listenning)(struct TServer*);                /*!< Stop the asynchrone listening. */

    void(*Send_Broadcast)(struct TServer*, TMessage);       /*!< Send a message to all connected clients. */

    size_t(*CountClients)(struct TServer*);                 /*!< Get the number of connected clients. */

    void(*Free)(struct TServer*);                           /*!< Free (ressources) method. */

    /* Callbacks */

    void(*On_Connect)(struct TServer*, TClient*);           /*!< Callback called when a client arrive.*/

    void(*On_Message)(struct TServer*, TClient*, TMessage); /*!< Callback called when a message is receive. */

    void(*On_Disconnect)(struct TServer*, TClient*);        /*!< Callback called when a client leave. */

    SOCKET server_sock;                                     /*!< The socket used by the server.*/
    unsigned int is_listenning;                             /*!< An boolean to know if the server is listening for new clients. */
    size_t max_c;                                           /*!< The maximum number of clients allowed to connect to the server. */
    pthread_t server_thread;                                /*!< The thread used for listening. */
    TClient_Node *clients_head;                             /*!< The list of connected clients. */

} TServer ;

/**
 * @fn TServer* New_TServer(unsigned short int port, size_t max_c)
 * @brief The constructor for create a TServer object.
 *
 * @param port The port to listening.
 * @param max_c The maximum number of clients allowed to connect.
 * @return A memory allocated object of the server.
 */
TServer* New_TServer(unsigned short int port, size_t max_c);

/**
 * @fn void TServer_Start_Listenning(TServer *this)
 * @brief Start listening for new clients. (Asynchrone)
 *
 * @param this A pointer to the client object.
 *
 * You do not have to call this method directly. You must use the
 * Start_Listenning method of the TClient structure like this:
 * my_server->Start_Listenning(my_server);
 */
void TServer_Start_Listenning(TServer *this);

/**
 * @fn void TServer_Stop_Listenning(TServer *this)
 * @brief Stop listening for new clients.
 *
 * @param this A pointer to the client object.
 *
 * You do not have to call this method directly. You must use the
 * Stop_Listenning method of the TClient structure like this:
 * my_server->Stop_Listenning(my_server);
 */
void TServer_Stop_Listenning(TServer *this);

/**
 * @fn void TServer_Send_Broadcast(TServer *this, TMessage message)
 * @brief Send a message to all connected clients.
 *
 * @param this A pointer to the client object.
 * @param message The message to send.
 *
 * You do not have to call this method directly. You must use the
 * Send_Broadcast method of the TClient structure like this:
 * my_server->Send_Broadcast(my_server, message);
 */
void TServer_Send_Broadcast(TServer *this, TMessage message);

/**
 * @fn size_t TServer_CountClients(TServer *this)
 * @brief Return the number of connected clients.
 *
 * @param this A pointer to the client object.
 * @return The number of connected clients.
 *
 * You do not have to call this method directly. You must use the
 * CountClients method of the TClient structure like this:
 * my_server->CountClients(my_server);
 */
size_t TServer_CountClients(TServer *this);

/**
 * @fn void TServer_New_Free(TServer *this)
 * @brief Method to free all ressources take by the server and clients.
 *
 * @param this A pointer to the client object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TClient structure like this:
 * my_server->Free(my_server);
 */
void TServer_New_Free(TServer *this);

#endif

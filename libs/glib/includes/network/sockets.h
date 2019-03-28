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
 * @file sockets.h
 * @brief Header file for define socket API functions.
 *
 * Header file for define socket API functions.
 *
 */

#ifndef GLIB_SOCKETS_H_
#define GLIB_SOCKETS_H_

#ifdef _WIN32

#include <winsock2.h>

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>

#define INVALID_SOCKET -1                   /*!< The INVALID_SOCKET cross-platform. */
#define SOCKET_ERROR -1                     /*!< The SOCKET_ERROR cross-platform. */
#define closesocket(s) close(s)             /*!< Cross-platform function for close a socket. */

typedef int SOCKET;                         /*!< Force the SOCKET type to be an integer. */
typedef struct sockaddr_in SOCKADDR_IN;     /*!< Rename for Windows compatibility. */
typedef struct sockaddr SOCKADDR;           /*!< Rename for Windows compatibility. */
typedef struct in_addr IN_ADDR;             /*!< Rename for Windows compatibility. */

#endif

/**
 * @fn int InitNetworking(void)
 * @brief Initialize the sockets API according to your operating system.
 *
 * @return Returns 0 if everything went well, otherwise a specific error code is returned.
 */
int InitNetworking(void);

/**
 * @fn int ResetNetworking(void)
 * @brief Reset and finish the sockets API according to your operating system.
 *
 * @return Returns 0 if everything went well, otherwise a specific error code is returned.
 */
int ResetNetworking(void);

/**
 * @fn int SocketNonBlocking(SOCKET socket, unsigned int blocking)
 * @brief Set a specific socket into blocking or non-blocking state.
 *
 * @param socket The socket to modifiy.
 * @param blocking Put 1 to put the socket in blocking state, 0 for the opposite.
 * @return Returns 0 if everything went well, otherwise a specific error code is returned.
 */
int SocketNonBlocking(SOCKET socket, unsigned int blocking);

#endif

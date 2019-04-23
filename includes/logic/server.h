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
 * @file logic/server.h
 * @brief Header file of the server logic.
 *
 * All methods for server logic are here.
 *
 */

#ifndef LOGIC_SERVER_H_
#define LOGIC_SERVER_H_

#include "network/game/server.h"
#include "network/message.h"
#include "network/client.h"

/**
 * @brief Function that apply the server logic corresponding to the packet type received.
 *
 * @param server A pointer to the server instance.
 * @param client A pointer to the client who send the message.
 * @param message The message sended via socket.
 * @param packet_id The message type.
 */
void handle_server_logic(TGameServer *server, TClient *client, TMessage message, int packet_id);

#endif

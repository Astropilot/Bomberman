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
 * @file logic/client.h
 * @brief Header file of the client logic.
 *
 * All methods for client logic are here.
 *
 */

#ifndef LOGIC_CLIENT_H_
#define LOGIC_CLIENT_H_

#include "network/game/client.h"
#include "network/message.h"

/**
 * @brief Function that apply the game logic corresponding to the packet type received.
 *
 * @param game A pointer to the game instance.
 * @param message The message sended via socket.
 * @param packet_id The message type.
 */
void handle_game_logic(TGameClient *game, TMessage message, int packet_id);

#endif

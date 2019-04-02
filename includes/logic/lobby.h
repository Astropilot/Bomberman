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
 * @file lobby.h
 * @brief Header file of the lobby logic.
 *
 * All methods for lobby logic are here.
 *
 */

#ifndef LOGIC_LOBBY_H_
#define LOGIC_LOBBY_H_

#include "network/game/lobby.h"
#include "network/message.h"

/**
 * @fn void handle_lobby_logic(TLobbyClient *lobby, TMessage message, int packet_id)
 * @brief Function that apply the lobby logic corresponding to the packet type received.
 *
 * @param lobby A pointer to the lobby instance.
 * @param message The message sended via socket.
 * @param packet_id The message type.
 */
void handle_lobby_logic(TLobbyClient *lobby, TMessage message, int packet_id);

#endif

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
 * @file ui/frame_lobby.h
 * @brief Header file of the Lobby TFrame class.
 *
 * This file allow you to instantiate a new Lobby TFrame.
 *
 */

#ifndef FRAME_LOBBY_H_
#define FRAME_LOBBY_H_

#include "glib.h"
#include "network/game/lobby.h"

/**
 * @fn TFrame* New_LobbyFrame(TLobbyClient *m_lobbyclient)
 * @brief The constructor for create a Lobby frame object.
 *
 * @param m_lobbyclient A pointer to the lobby client.
 * @return A memory allocated object of the Lobby frame.
 */
TFrame* New_LobbyFrame(TLobbyClient *m_lobbyclient);

#endif

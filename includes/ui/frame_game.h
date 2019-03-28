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
 * @file frame_end_game.h
 * @brief Header file of the Game TFrame class.
 *
 * This file allow you to instantiate a new Game TFrame.
 *
 */

#ifndef FRAME_GAME_H_
#define FRAME_GAME_H_

#include "glib.h"
#include "network/game/client.h"

/**
 * @fn TFrame* New_GameFrame(TGameClient *m_gameclient)
 * @brief The constructor for create a Game frame object.
 *
 * @param m_gameclient A pointer to the game client.
 * @return A memory allocated object of the Game frame.
 */
TFrame* New_GameFrame(TGameClient *m_gameclient);

/**
 * @fn void GameFrame_UpdatePlayerInfo(TFrame *frame, player_t player)
 * @brief Additional method for update a info-box of a player.
 *
 * @param frame The actual GameFrame instance.
 * @param player The player info to be updated.
 */
void GameFrame_UpdatePlayerInfo(TFrame *frame, player_t player);

#endif

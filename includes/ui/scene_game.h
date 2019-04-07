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
 * @file ui/scene_game.h
 * @brief Header file of the Game TScene class.
 *
 * This file allow you to instantiate a new Game TScene.
 *
 */

#ifndef SCENE_GAME_H_
#define SCENE_GAME_H_

#include "glib.h"
#include "network/game/client.h"

/**
 * @fn TScene* New_GameScene(TGameClient *m_gameclient)
 * @brief The constructor for create a Game scene object.
 *
 * @param m_gameclient A pointer to the game client.
 * @return A memory allocated object of the Game scene.
 */
TScene* New_GameScene(TGameClient *m_gameclient);

/**
 * @fn void GameScene_UpdatePlayerInfo(TScene *scene, player_t player)
 * @brief Additional method for update a info-box of a player.
 *
 * @param scene The actual GameScene instance.
 * @param player The player info to be updated.
 */
void GameScene_UpdatePlayerInfo(TScene *scene, player_t player);

#endif

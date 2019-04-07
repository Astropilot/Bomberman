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
 * @file ui/scene_end_game.h
 * @brief Header file of the End Game TScene class.
 *
 * This file allow you to instantiate a new End Game TScene.
 *
 */

#ifndef SCENE_END_GAME_H_
#define SCENE_END_GAME_H_

#include "glib.h"

/**
 * @fn TScene* New_EndGameScene(void)
 * @brief The constructor for create a End Game scene object.
 *
 * @return A memory allocated object of the End Game scene.
 */
TScene* New_EndGameScene(void);

#endif

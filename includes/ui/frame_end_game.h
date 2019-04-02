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
 * @file ui/frame_end_game.h
 * @brief Header file of the End Game TFrame class.
 *
 * This file allow you to instantiate a new End Game TFrame.
 *
 */

#ifndef FRAME_END_GAME_H_
#define FRAME_END_GAME_H_

#include "glib.h"

/**
 * @fn TFrame* New_EndGameFrame(void)
 * @brief The constructor for create a End Game frame object.
 *
 * @return A memory allocated object of the End Game frame.
 */
TFrame* New_EndGameFrame(void);

#endif

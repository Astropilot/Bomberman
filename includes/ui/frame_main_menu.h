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
 * @file frame_main_menu.h
 * @brief Header file of the Main Menu TFrame class.
 *
 * This file allow you to instantiate a new Main Menu TFrame.
 *
 */

#ifndef FRAME_MAIN_MENU_H_
#define FRAME_MAIN_MENU_H_

#include "glib.h"

/**
 * @fn TFrame* New_MainMenuFrame(void)
 * @brief The constructor for create a Main Menu frame object.
 *
 * @return A memory allocated object of the Main Menu frame.
 */
TFrame* New_MainMenuFrame(void);

#endif

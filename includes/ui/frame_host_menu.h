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
 * @file ui/frame_host_menu.h
 * @brief Header file of the Host Menu TFrame class.
 *
 * This file allow you to instantiate a new Host Menu TFrame.
 *
 */

#ifndef FRAME_HOST_MENU_H_
#define FRAME_HOST_MENU_H_

#include "glib.h"

/**
 * @fn TFrame* New_HostMenuFrame(void)
 * @brief The constructor for create a Host Menu frame object.
 *
 * @return A memory allocated object of the Host Menu frame.
 */
TFrame* New_HostMenuFrame(void);

#endif

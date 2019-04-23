/*******************************************************************************
* PROJECT: gLib
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
 * @file resource.h
 * @brief Header file of resource manipulation.
 *
 * This file have manipulation functions for resources.
 *
 */

#ifndef GLIB_RESOURCE_H_
#define GLIB_RESOURCE_H_

#include <SDL2/SDL.h>

#include "window.h"

/**
 * @brief Function for load and create a SDL_Surface and SDL_Texture.
 *
 * @param window A pointer to the window object.
 * @param path The path of the resource.
 * @param surface A pointer to the SDL Surface pointer that will be created.
 * @param texture A pointer to the SDL Texture pointer that will be created.
 * @return Return 1 if the resource has been successfully loaded, otherwise 0.
 */
unsigned int loadImageResource(TWindow *window, const char *path, SDL_Surface **surface, SDL_Texture **texture);

#endif

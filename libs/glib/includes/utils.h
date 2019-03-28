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
 * @file utils.h
 * @brief Header file of some internal utils of GLib.
 *
 * This file have some utils for internal purpose in GLib.
 *
 */

#ifndef GLIB_UTILS_H_
#define GLIB_UTILS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct TFrame TFrame;

/**
 * @fn SDL_Texture *createText(TFrame *frame, const char *text, TTF_Font *font, SDL_Color color, SDL_Rect *pos)
 * @brief Util function for create a SDL texture from a text, a font and a color.
 *
 * @param frame A pointer to the window object.
 * @param text The text.
 * @param font The font of the text.
 * @param color The color of the text.
 * @param pos The position of the text.
 * @return A pointer to a SDL_Texture of the text.
 */
SDL_Texture *createText(TFrame *frame, const char *text, TTF_Font *font, SDL_Color color, SDL_Rect *pos);

/**
 * @fn TTF_Font *loadFont(const char *font_file, size_t font_size)
 * @brief Util function for load a font file with a specific size.
 *
 * @param font_file The path of the font file.
 * @param font_size The font size to be used for rendering.
 * @return A pointer to a TTF_Font or NULL if the load failed.
 */
TTF_Font *loadFont(const char *font_file, size_t font_size);

/**
 * @fn unsigned long hash(const char *str)
 * @brief Util function for hash a string into a unsigned long number.
 *
 * @param str The string to hash.
 * @return The unsigned long that represent the string.
 */
unsigned long hash(const char *str);

#endif

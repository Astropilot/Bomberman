/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Header file of some internal utils of GLib.
*/

/**
 * @file utils.h
 * @brief Header file of some internal utils of GLib.
 * @author Yohann.M, Gauthier.D, Aziz.H, William.W
 * @version 1.0
 * @date 28 janvier 2019
 *
 * This file have some utils for internal purpose in GLib.
 *
 */

#ifndef GLIB_UTILS_H_
#define GLIB_UTILS_H_

#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct TWindow TWindow;

/**
 * @fn SDL_Texture *createText(const char *text, TTF_Font *font, SDL_Color color, SDL_Rect *pos, TWindow *win)
 * @brief Util function for create a SDL texture from a text, a font and a color.
 *
 * @param text The text.
 * @param font The font of the text.
 * @param color The color of the text.
 * @param pos The position of the text.
 * @param win A pointer to the window object.
 * @return A pointer to a SDL_Texture of the text.
 */
SDL_Texture *createText(const char *text, TTF_Font *font, SDL_Color color, SDL_Rect *pos, TWindow *win);

#endif

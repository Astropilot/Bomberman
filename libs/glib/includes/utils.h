/*
** ETNA PROJECT, 16/01/2019 by group
** gLib
** File description:
**      Graphic library with SDL2
*/

#ifndef UTILS_H_
#define UTILS_H_

#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct TWindow TWindow;

SDL_Texture *createText(const char *text, TTF_Font *font, SDL_Color color, SDL_Rect *pos, TWindow *win);

#endif

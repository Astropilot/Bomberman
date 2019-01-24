/*
** ETNA PROJECT, 16/01/2019 by group
** gLib
** File description:
**      Graphic library with SDL2
*/

#ifndef GLIB_SPRITE_H_
#define GLIB_SPRITE_H_

#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct TWindow TWindow;

typedef struct TSprite {

    void(*Draw)(struct TSprite*, TWindow*);

    void(*Free)(struct TSprite*);

    SDL_Texture *texture;
    SDL_Rect pos;
    char *file;

} TSprite ;

TSprite* New_TSprite(TWindow *win, const char *file, SDL_Rect size);
void TSprite_Draw(TSprite *this, TWindow *win);
void TSprite_New_Free(TSprite *this);

#endif

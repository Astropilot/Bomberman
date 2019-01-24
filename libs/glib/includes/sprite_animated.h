/*
** ETNA PROJECT, 16/01/2019 by group
** gLib
** File description:
**      Graphic library with SDL2
*/

#ifndef GLIB_SPRITE_ANIMATED_H_
#define GLIB_SPRITE_ANIMATED_H_

#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct TWindow TWindow;

typedef struct TAnimatedSprite {

    void(*Draw)(struct TAnimatedSprite*, TWindow*);

    void(*Free)(struct TAnimatedSprite*);

    SDL_Texture *texture;
    SDL_Rect pos;
    char *file;
    size_t speed;
    size_t len_frames;
    unsigned int actual_frame;
    unsigned int last_time;

} TAnimatedSprite ;

TAnimatedSprite* New_TAnimatedSprite(TWindow *win, const char *file, SDL_Rect pos, size_t speed);
void TAnimatedSprite_Draw(TAnimatedSprite *this, TWindow *win);
void TAnimatedSprite_New_Free(TAnimatedSprite *this);

#endif

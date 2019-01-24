/*
** ETNA PROJECT, 16/01/2019 by group
** gLib
** File description:
**      Graphic library with SDL2
*/

#ifndef GLIB_INPUTBOX_H_
#define GLIB_INPUTBOX_H_

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "sprite.h"
#include "window.h"
#include "utils.h"

#define MAX_STR_LEN 15

typedef struct TInput {

    void(*Draw)(struct TInput*, TWindow*);

    void(*Event_Handler)(struct TInput*, TWindow *, SDL_Event);

    void(*Free)(struct TInput*);

    char text[MAX_STR_LEN];
    TSprite *input_sprite;
    TTF_Font *font;
    SDL_Color color;
    SDL_Rect pos_input;
    SDL_Rect pos_text;
    unsigned int is_focus;
    unsigned int last_time;

} TInput ;

TInput* New_TInput(const char *sprite_file, SDL_Rect pos, TWindow *window, SDL_Color color);
void TInput_Draw(TInput *this, TWindow *window);
void TInput_Event_Handler(TInput *this, TWindow *win, SDL_Event event);
void TInput_New_Free(TInput *this);

#endif
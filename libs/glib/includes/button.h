/*
** ETNA PROJECT, 16/01/2019 by group
** gLib
** File description:
**      Graphic library with SDL2
*/

#ifndef GLIB_BUTTON_H_
#define GLIB_BUTTON_H_

#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "sprite.h"

typedef enum EButton_State {
    BUTTON_NORMAL,
    BUTTON_HOVER
} EButton_State ;

typedef struct TButton {

    void(*Draw)(struct TButton*, TWindow*);

    void(*On_Click)(struct TButton*, TWindow*);

    void(*Event_Handler)(struct TButton*, TWindow *, SDL_Event);

    void(*Free)(struct TButton*);

    TSprite *btn_sprite;
    TSprite *btn_hover_sprite;
    EButton_State state;
    SDL_Rect pos;

} TButton ;

TButton* New_TButton(const char *btn_s, const char *btn_hs, SDL_Rect pos, TWindow *win);
void TButton_Draw(TButton *this, TWindow *window);
void TButton_Event_Handler(TButton *this, TWindow *win, SDL_Event event);
void TButton_New_Free(TButton *this);

#endif

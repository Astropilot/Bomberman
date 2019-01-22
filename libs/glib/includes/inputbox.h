/*
** ETNA PROJECT, 16/01/2019 by group
** gLib
** File description:
**      Graphic library with SDL2
*/

#ifndef INPUTBOX_H_
#define INPUTBOX_H_

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
    /*  Les pointeurs sur fonctions (membres) :                       */

    void(*Draw)(struct TInput*, TWindow*);

    // A chaque évènement SDL
    void(*Event_Handler)(struct TInput*, TWindow *, SDL_Event);

    // Libération des ressources et destruction de l'objet
    void(*Free)(struct TInput*);

    /*  Les données membres :                                         */
    char text[MAX_STR_LEN];
    TSprite *input_sprite;
    TTF_Font *font;
    SDL_Color color;
    SDL_Rect pos_input;
    SDL_Rect pos_text;
    unsigned int is_focus;
    unsigned int last_time;
    // Liste de sprites (textures)

} TInput ;

TInput* New_TInput(const char *sprite_file, SDL_Rect pos, TWindow *window, SDL_Color color);
void TInput_Draw(TInput *this, TWindow *window);
void TInput_Event_Handler(TInput *this, TWindow *win, SDL_Event event);
void TInput_New_Free(TInput *this);

#endif

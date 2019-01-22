/*
** ETNA PROJECT, 16/01/2019 by group
** gLib
** File description:
**      Graphic library with SDL2
*/

#ifndef TEXT_H_
#define TEXT_H_

#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "utils.h"

typedef struct TWindow TWindow;

typedef struct TText {
    /*  Les pointeurs sur fonctions (membres) :                       */

    // Desinne le sprite dans le buffer
    void(*Draw)(struct TText*, TWindow*);

    // Libération des ressources et destruction de l'objet
    void(*Free)(struct TText*);

    /*  Les données membres :                                         */
    char *text;
    SDL_Texture *texture;
    SDL_Rect pos;

} TText ;

TText* New_TText(const char *text, TWindow *win, TTF_Font *font, SDL_Color color, SDL_Rect pos);
void TText_Draw(TText *this, TWindow *win);
void TText_New_Free(TText *this);

#endif

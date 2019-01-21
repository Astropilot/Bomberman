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
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct TInput {
    /*  Les pointeurs sur fonctions (membres) :                       */

    // Libération des ressources et destruction de l'objet
    void(*Free)(struct TInput*);

    /*  Les données membres :                                         */
    char *text_entry;
    TSprite *btn_sprite;
    SDL_Rect pos;
    // Liste de sprites (textures)

} TInput ;

TInput* New_TInput();
void TInput_New_Free(TInput *this);

#endif

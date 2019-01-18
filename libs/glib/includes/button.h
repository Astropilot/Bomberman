/*
** ETNA PROJECT, 16/01/2019 by group
** gLib
** File description:
**      Graphic library with SDL2
*/

#ifndef BUTTON_H_
#define BUTTON_H_

#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "sprite.h"

typedef struct TButton {
    /*  Les pointeurs sur fonctions (membres) :                       */

    // Executé une seul fois lors de l'ajout à la fenêtre principale
    void(*Init)(struct TButton*, TWindow*);

    // Executé à chaque fois que cette Frame devient celle visible
    void(*On_Click)(struct TButton*, TWindow*);

    // A chaque évènement SDL
    void(*Event_Handler)(struct TButton*, SDL_Event);

    // Libération des ressources et destruction de l'objet
    void(*Free)(struct TButton*);

    /*  Les données membres :                                         */
    char *text;
    TSprite *btn_sprite;
    TSprite *btn_hover_sprite;
    SDL_Rect pos;
    // Liste de sprites (textures)

} TButton ;

TButton* New_TButton(const char *text, int w, int h);
void TFrame_Event_Handler(TButton *this, SDL_Event event);
void TFrame_New_Free(TFrame *this);

#endif

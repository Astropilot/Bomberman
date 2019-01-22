/*
** ETNA PROJECT, 16/01/2019 by group
** gLib
** File description:
**      Graphic library with SDL2
*/

#ifndef SPRITE_H_
#define SPRITE_H_

#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct TWindow TWindow;

typedef struct TSprite {
    /*  Les pointeurs sur fonctions (membres) :                       */

    // Desinne le sprite dans le buffer
    void(*Draw)(struct TSprite*, TWindow*);

    // Libération des ressources et destruction de l'objet
    void(*Free)(struct TSprite*);

    /*  Les données membres :                                         */
    SDL_Texture *texture;
    SDL_Rect pos;
    char *file;

} TSprite ;

/* Linked list
typedef struct TSprite_Node {
    TSprite *sprite;
    struct TSprite_Node *next;
} TSprite_Node ;*/

TSprite* New_TSprite(TWindow *win, const char *file, SDL_Rect size);
void TSprite_Draw(TSprite *this, TWindow *win);
void TSprite_New_Free(TSprite *this);

#endif

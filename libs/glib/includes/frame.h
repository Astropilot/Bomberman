/*
** ETNA PROJECT, 16/01/2019 by group
** gLib
** File description:
**      Graphic library with SDL2
*/

#ifndef FRAME_H_
#define FRAME_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "sprite.h"
#include "drawables.h"

typedef struct TWindow TWindow;

typedef struct TFrame {
    /*  Les pointeurs sur fonctions (membres) :                       */

    void(*Add_Drawable)(struct TFrame*, void*, drawables_e, const char*, unsigned int);

    //void(*AddTop_Sprite)(struct TFrame*, TSprite*);

    void*(*Remove_Drawable)(struct TFrame*, const char *id);

    void*(*Get_Drawable)(struct TFrame*, const char *id);

    void(*Draw_Drawables)(struct TFrame*, TWindow*);

    // Executé une seul fois lors de l'ajout à la fenêtre principale
    void(*Init)(struct TFrame*, TWindow*);

    // Executé à chaque fois que cette Frame devient celle visible
    void(*On_Load)(struct TFrame*, TWindow*, va_list args);

    // A chaque évènement SDL
    void(*On_Event)(struct TFrame*, TWindow*, SDL_Event);

    // A chaque tour de boucle
    void(*On_Tick)(struct TFrame*, TWindow*);

    // Executé à chaque fois que cette Frame ne sera plus affichée.
    void(*On_Unload)(struct TFrame*, TWindow*);

    // Executé lorsque la fenêtre dois se fermer
    void(*Finish)(struct TFrame*, TWindow*);

    // Libération des ressources et destruction de l'objet
    void(*Free)(struct TFrame*);

    /*  Les données membres :                                         */
    char *frame_id;
    unsigned int initialized;
    // Liste de sprites (textures)
    Drawable_Node *drawables_head;

} TFrame ;

/* Linked list */
typedef struct TFrame_Node {
    TFrame *frame;
    struct TFrame_Node *next;
} TFrame_Node ;

TFrame* New_TFrame(const char *frame_id);
void TFrame_Add_Drawable(TFrame *this, void *drawable, drawables_e type, const char *id, unsigned int priority);
//void TFrame_AddTop_Sprite(TFrame *this, TSprite *sprite);
void *TFrame_Remove_Drawable(TFrame *this, const char *id);
void *TFrame_Get_Drawable(TFrame *this, const char *id);
void TFrame_Draw_Drawables(TFrame *this, TWindow *win);
void TFrame_New_Free(TFrame *this);

#endif

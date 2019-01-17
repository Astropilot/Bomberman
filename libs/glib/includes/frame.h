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
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct TWindow TWindow;

typedef struct TFrame {
    /*  Les pointeurs sur fonctions (membres) :                       */

    // Executé une seul fois lors de l'ajout à la fenêtre principale
    void(*Init)(struct TFrame*, TWindow*);

    // Executé à chaque fois que cette Frame devient celle visible
    void(*On_Load)(struct TFrame*, TWindow*);

    // A chaque évènement SDL
    void(*On_Event)(struct TFrame*, TWindow*, SDL_Event);

    // A chaque tour de boucle
    void(*On_Tick)(struct TFrame*, TWindow*);

    // Executé lorsque la fenêtre dois se fermer
    void(*Finish)(struct TFrame*, TWindow*);

    // Libération des ressources et destruction de l'objet
    void(*Free)(struct TFrame*);

    /*  Les données membres :                                         */
    char *frame_id;
    unsigned int initialized;
    // Liste de sprites (textures)

} TFrame ;

/* Linked list */
typedef struct TFrame_Node {
    TFrame *frame;
    struct TFrame_Node *next;
} TFrame_Node ;

TFrame* New_TFrame(const char *frame_id);
void TFrame_On_Load(TFrame *this, TWindow *window);
void TFrame_On_Event(TFrame *this, TWindow *window, SDL_Event event);
void TFrame_On_Tick(TFrame *this, TWindow *window);
void TFrame_New_Free(TFrame *this);

#endif

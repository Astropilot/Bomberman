/*
** ETNA PROJECT, 16/01/2019 by group
** gLib
** File description:
**      Graphic library with SDL2
*/

#ifndef GLIB_FRAME_H_
#define GLIB_FRAME_H_

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

    void(*Add_Drawable)(struct TFrame*, void*, drawables_e, const char*, unsigned int);

    void*(*Remove_Drawable)(struct TFrame*, const char *id);

    void*(*Get_Drawable)(struct TFrame*, const char *id);

    void(*Draw_Drawables)(struct TFrame*, TWindow*);

    void(*Init)(struct TFrame*, TWindow*);

    void(*On_Load)(struct TFrame*, TWindow*, va_list args);

    void(*On_Event)(struct TFrame*, TWindow*, SDL_Event);

    void(*On_Tick)(struct TFrame*, TWindow*);

    void(*On_Unload)(struct TFrame*, TWindow*);

    void(*Finish)(struct TFrame*, TWindow*);

    void(*Free)(struct TFrame*);

    char *frame_id;
    unsigned int initialized;
    Drawable_Node *drawables_head;

} TFrame ;

typedef struct TFrame_Node {
    TFrame *frame;
    struct TFrame_Node *next;
} TFrame_Node ;

TFrame* New_TFrame(const char *frame_id);
void TFrame_Add_Drawable(TFrame *this, void *drawable, drawables_e type, const char *id, unsigned int priority);
void *TFrame_Remove_Drawable(TFrame *this, const char *id);
void *TFrame_Get_Drawable(TFrame *this, const char *id);
void TFrame_Draw_Drawables(TFrame *this, TWindow *win);
void TFrame_New_Free(TFrame *this);

#endif

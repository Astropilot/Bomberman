/*
** ETNA PROJECT, 16/01/2019 by group
** gLib
** File description:
**      Graphic library with SDL2
*/

#ifndef GLIB_DRAWABLES_H_
#define GLIB_DRAWABLES_H_

#include <stdlib.h>
#include <unistd.h>

typedef struct TWindow TWindow;

typedef enum drawables_e {
    SPRITE,
    ANIMATED_SPRITE,
    TEXT,
    BUTTON,
    INPUT
} drawables_e ;

typedef struct Drawable_Node {
    char *id;
    unsigned int priority;
    drawables_e type;
    void *drawable;
    struct Drawable_Node *next;
} Drawable_Node ;

void drawableCallDraw(Drawable_Node *drawable, TWindow *win);
void drawableCallFree(Drawable_Node *drawable);

#endif

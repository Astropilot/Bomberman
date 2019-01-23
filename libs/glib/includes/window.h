/*
** ETNA PROJECT, 16/01/2019 by group
** gLib
** File description:
**      Graphic library with SDL2
*/

#ifndef WINDOW_H_
#define WINDOW_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "frame.h"

typedef struct TWindow {

    int(*Create_Window)(struct TWindow*, const char*, int, int, const char*);
    void(*Add_Frame)(struct TWindow*, TFrame*);
    void(*Show_Frame)(struct TWindow*, const char *, int argc, ...);
    void(*Free)(struct TWindow*);

    SDL_Window *screen_window;
    SDL_Renderer *renderer_window;
    unsigned int finished;
    TFrame_Node *frames_head;
    TFrame *shown_frame;

} TWindow ;

TWindow* New_TWindow(void);
int TWindow_Create_Window(TWindow *this, const char *title, int width, int height, const char *frame_id);
void TWindow_Add_Frame(TWindow *this, TFrame *frame);
void TWindow_Show_Frame(TWindow *this, const char *frame_id, int argc, ...);
void TWindow_New_Free(TWindow *this);

#endif

/*******************************************************************************
* PROJECT: gLib
*
* AUTHORS: Yohann Martin, Aziz Hamide, Gauthier Desplanque, William Weber
*
* DATE CREATED: 01/16/2019
*
* Copyright (c) 2019 Yohann MARTIN (@Astropilot). All rights reserved.
*
* Licensed under the MIT License. See LICENSE file in the project root for full
* license information.
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "window.h"

static void TWindow_Init(TWindow *this);
static void TWindow_Free_Frames(TWindow *this);
static void TWindow_Finish_Frames(TWindow *this);
static void TWindow_Loop(TWindow *this);

TWindow* New_TWindow(void)
{
    TWindow *this = malloc(sizeof(TWindow));

    if(!this) return (NULL);
    TWindow_Init(this);
    this->Free = TWindow_New_Free;
    return (this);
}

static void TWindow_Init(TWindow *this)
{
    if (!this) return;

    this->Create_Window = TWindow_Create_Window;
    this->Add_Frame = TWindow_Add_Frame;
    this->Show_Frame = TWindow_Show_Frame;
    this->screen_window = NULL;
    this->renderer_window = NULL;
    this->finished = 0;
    this->frames_head = NULL;
    this->shown_frame = NULL;
}

static void TWindow_Free_Frames(TWindow *this)
{
    if (!this) return;

    TFrame_Node *current = this->frames_head;
    TFrame_Node *tmp = NULL;

    while (current != NULL) {
        if (current->frame && current->frame->Free)
            current->frame->Free(current->frame);

        tmp = current;
        current = current->next;
        free(tmp);
    }
}

static void TWindow_Finish_Frames(TWindow *this)
{
    if (!this) return;

    TFrame_Node *current = this->frames_head;

    while (current != NULL) {
        if (current->frame && current->frame->Finish)
            current->frame->Finish(current->frame);
        current = current->next;
    }
}

static void TWindow_Loop(TWindow *this)
{
    SDL_Event event;
    unsigned int current_time = 0;
    unsigned int last_time = 0;

    if (!this) return;

    while (!this->finished) {
        while( SDL_PollEvent( &event ) != 0 ) {
            if( event.type == SDL_QUIT )
                this->finished = 1;
            else {
                if (this->shown_frame && this->shown_frame->On_Event)
                    this->shown_frame->On_Event(this->shown_frame, event);
            }
        }
        if (this->shown_frame && this->shown_frame->On_Tick) {
            current_time = SDL_GetTicks();
            if (current_time > last_time + this->fps || this->finished) {
                this->shown_frame->On_Tick(this->shown_frame);
                last_time = current_time;
            }
        }
    }
    TWindow_Finish_Frames(this);
}

int TWindow_Create_Window(TWindow *this, const char *title, int width, int height, const char *frame_id, unsigned int fps)
{
    if (!this || !title || !frame_id) return (0);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error while loading game window (SDL): %s!\n", SDL_GetError());
        return (0);
    }

    this->screen_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    width,
                                    height,
                                    SDL_WINDOW_SHOWN);
    if (this->screen_window == NULL) {
        fprintf(stderr, "Error while loading game window (SDL): %s!\n", SDL_GetError());
        return (0);
    }
    this->renderer_window = SDL_CreateRenderer(this->screen_window, -1, SDL_RENDERER_ACCELERATED);
    if (this->renderer_window == NULL) {
        fprintf(stderr, "Error while loading game window (SDL): %s!\n", SDL_GetError());
        return (0);
    }

    if ( (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG ) {
        fprintf(stderr, "Error while loading IMG Plugin (SDL): %s!\n", IMG_GetError());
        return (0);
    }

    if(TTF_Init() == -1) {
        fprintf(stderr, "Error while loading TTF (SDL): %s!\n", TTF_GetError());
        return (0);
    }

    this->fps = fps;
    TWindow_Show_Frame(this, frame_id, 0);
    TWindow_Loop(this);

    return (1);
}

void TWindow_Add_Frame(TWindow *this, TFrame *frame)
{
    if (!this || !frame) return;

    frame->window = this;
    if (!this->frames_head) {
        TFrame_Node *frame_node = malloc(sizeof(TFrame_Node));

        if (frame_node) {
            frame_node->frame = frame;
            frame_node->next = NULL;
            this->frames_head = frame_node;
        }
    } else {
        TFrame_Node *current = this->frames_head;

        while (current->next != NULL)
            current = current->next;
        current->next = malloc(sizeof(TFrame_Node));
        if (current->next) {
            current->next->frame = frame;
            current->next->next = NULL;
        }
    }
}

void TWindow_Show_Frame(TWindow *this, const char *frame_id, int argc, ...)
{
    if (!this || !frame_id) return;

    TFrame_Node *current = this->frames_head;
    TFrame *tmp_shown_frame = NULL;

    while (current != NULL) {
        if (current->frame && strcmp(current->frame->frame_id, frame_id) == 0) {
            tmp_shown_frame = this->shown_frame;
            this->shown_frame = NULL;
            if (tmp_shown_frame && tmp_shown_frame->On_Unload)
                tmp_shown_frame->On_Unload(tmp_shown_frame);
            if (tmp_shown_frame)
                tmp_shown_frame->Free_All_Drawables(tmp_shown_frame, GLIB_FREE_ON_UNLOAD);
            if (!current->frame->initialized && current->frame->Init) {
                current->frame->Init(current->frame);
                current->frame->initialized = 1;
            }
            va_list argp;
            va_start(argp, argc);
            if (current->frame->On_Load)
                current->frame->On_Load(current->frame, argc, argp);
            va_end(argp);
            this->shown_frame = current->frame;
            return;
        }
        current = current->next;
    }
}

void TWindow_New_Free(TWindow *this)
{
    if (this) {
        TWindow_Free_Frames(this);
        TTF_Quit();
        IMG_Quit();
        SDL_DestroyRenderer(this->renderer_window);
        SDL_DestroyWindow(this->screen_window);
        SDL_Quit();
    }
    free(this);
}

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

static void TWindow_Init(TWindow *this, unsigned int max_caching);
static void TWindow_Free_Scenes(TWindow *this);
static void TWindow_Finish_Scenes(TWindow *this);
static void TWindow_Loop(TWindow *this);

TWindow* New_TWindow(unsigned int max_caching)
{
    TWindow *this = malloc(sizeof(TWindow));

    if(!this) return (NULL);
    TWindow_Init(this, max_caching);
    this->Free = TWindow_New_Free;
    return (this);
}

static void TWindow_Init(TWindow *this, unsigned int max_caching)
{
    if (!this) return;

    this->Create_Window = TWindow_Create_Window;
    this->Add_Scene = TWindow_Add_Scene;
    this->Show_Scene = TWindow_Show_Scene;
    this->screen_window = NULL;
    this->renderer_window = NULL;
    this->finished = 0;
    this->scenes_head = NULL;
    this->shown_scene = NULL;
    this->cache_manager = New_TResourceCache(this, max_caching);
}

static void TWindow_Free_Scenes(TWindow *this)
{
    if (!this) return;

    TScene_Node *current = this->scenes_head;
    TScene_Node *tmp = NULL;

    while (current != NULL) {
        if (current->scene && current->scene->Free)
            current->scene->Free(current->scene);

        tmp = current;
        current = current->next;
        free(tmp);
    }
}

static void TWindow_Finish_Scenes(TWindow *this)
{
    if (!this) return;

    TScene_Node *current = this->scenes_head;

    while (current != NULL) {
        if (current->scene && current->scene->Finish)
            current->scene->Finish(current->scene);
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
                if (this->shown_scene && this->shown_scene->On_Event)
                    this->shown_scene->On_Event(this->shown_scene, event);
            }
        }
        if (this->shown_scene && this->shown_scene->On_Tick) {
            current_time = SDL_GetTicks();
            if (current_time > last_time + this->fps || this->finished) {
                this->shown_scene->On_Tick(this->shown_scene);
                last_time = current_time;
            }
        }
    }
    TWindow_Finish_Scenes(this);
}

int TWindow_Create_Window(TWindow *this, const char *title, int width, int height, const char *scene_id, unsigned int fps)
{
    if (!this || !title || !scene_id) return (0);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
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
        fprintf(stderr, "Error while loading game window (SDL): %s\n", SDL_GetError());
        return (0);
    }

    if ( (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG ) {
        fprintf(stderr, "Error while loading IMG Plugin (SDL): %s\n", IMG_GetError());
        return (0);
    }

    if (TTF_Init() == -1) {
        fprintf(stderr, "Error while loading TTF (SDL): %s\n", TTF_GetError());
        return (0);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 ) == -1) {
        fprintf(stderr, "Error while loading SDL_mixer (SDL): %s\n", Mix_GetError());
        return (0);
    }
    Mix_AllocateChannels(10);

    this->fps = fps;
    TWindow_Show_Scene(this, scene_id, 0);
    TWindow_Loop(this);

    return (1);
}

void TWindow_Add_Scene(TWindow *this, TScene *scene)
{
    if (!this || !scene) return;

    scene->window = this;
    if (!this->scenes_head) {
        TScene_Node *scene_node = malloc(sizeof(TScene_Node));

        if (scene_node) {
            scene_node->scene = scene;
            scene_node->next = NULL;
            this->scenes_head = scene_node;
        }
    } else {
        TScene_Node *current = this->scenes_head;

        while (current->next != NULL)
            current = current->next;
        current->next = malloc(sizeof(TScene_Node));
        if (current->next) {
            current->next->scene = scene;
            current->next->next = NULL;
        }
    }
}

void TWindow_Show_Scene(TWindow *this, const char *scene_id, int argc, ...)
{
    if (!this || !scene_id) return;

    TScene_Node *current = this->scenes_head;
    TScene *tmp_shown_scene = NULL;

    while (current != NULL) {
        if (current->scene && strcmp(current->scene->scene_id, scene_id) == 0) {
            tmp_shown_scene = this->shown_scene;
            this->shown_scene = NULL;
            if (tmp_shown_scene && tmp_shown_scene->On_Unload)
                tmp_shown_scene->On_Unload(tmp_shown_scene);
            if (tmp_shown_scene)
                tmp_shown_scene->Free_All_Drawables(tmp_shown_scene, GLIB_FREE_ON_UNLOAD);
            if (!current->scene->initialized && current->scene->Init) {
                current->scene->Init(current->scene);
                current->scene->initialized = 1;
            }
            va_list argp;
            va_start(argp, argc);
            if (current->scene->On_Load)
                current->scene->On_Load(current->scene, argc, argp);
            va_end(argp);
            this->shown_scene = current->scene;
            return;
        }
        current = current->next;
    }
}

void TWindow_New_Free(TWindow *this)
{
    if (this) {
        TWindow_Free_Scenes(this);
        this->cache_manager->Free(this->cache_manager);
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        SDL_DestroyRenderer(this->renderer_window);
        SDL_DestroyWindow(this->screen_window);
        SDL_Quit();
    }
    free(this);
}

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

#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sprite.h"
#include "frame.h"
#include "window.h"
#include "resource.h"

static void TSprite_Init(TSprite *this, TFrame *frame, const char *file, SDL_Rect pos);

TSprite* New_TSprite(TFrame *frame, const char *file, SDL_Rect pos)
{
    TSprite *this = malloc(sizeof(TSprite));

    if(!this) return (NULL);
    TSprite_Init(this, frame, file, pos);
    this->Free = TSprite_New_Free;
    return (this);
}

static void TSprite_Init(TSprite *this, TFrame *frame, const char *file, SDL_Rect pos)
{
    if (!this || !frame || !file) return;

    //unsigned int res_load = 0;
    TResourceCache *cache = frame->window->cache_manager;

    //res_load = loadImageResource(frame->window, file, NULL, &(this->texture));
    //if (!res_load) return;
    this->texture = cache->FetchTexture(cache, file);
    if (!this->texture) return;
    this->Draw = TSprite_Draw;
    this->file = strdup(file);
    this->pos = pos;
    this->is_visible = 1;
}

void TSprite_Draw(TSprite *this, TFrame *frame)
{
    if (!this || !frame || !this->texture) return;

    SDL_RenderCopy(frame->window->renderer_window, this->texture, NULL, &this->pos);
}

void TSprite_New_Free(TSprite *this)
{
    if (this) {
        if (this->file)
            free(this->file);
        if (this->texture)
            SDL_DestroyTexture(this->texture);
    }
    free(this);
}

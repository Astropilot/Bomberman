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

#include "sprite_animated.h"
#include "frame.h"
#include "window.h"
#include "resource.h"

static void TAnimatedSprite_Init(TAnimatedSprite *this, TFrame *frame, const char *file, SDL_Rect size, SDL_Rect pos, size_t speed, int animations);

TAnimatedSprite* New_TAnimatedSprite(TFrame *frame, const char *file, SDL_Rect size, SDL_Rect pos, size_t speed, int animations)
{
    TAnimatedSprite *this = malloc(sizeof(TAnimatedSprite));

    if(!this) return (NULL);
    TAnimatedSprite_Init(this, frame, file, size, pos, speed, animations);
    this->Free = TAnimatedSprite_New_Free;
    return (this);
}

static void TAnimatedSprite_Init(TAnimatedSprite *this, TFrame *frame, const char *file, SDL_Rect size, SDL_Rect pos, size_t speed, int animations)
{
    if (!this || !frame || !file) return;

    //unsigned int res_load = 0;
    int w, h;
    TResourceCache *cache = frame->window->cache_manager;

    //res_load = loadImageResource(frame->window, file, NULL, &(this->texture));
    //if (!res_load) return;
    this->texture = cache->FetchTexture(cache, file);
    if (!this->texture) return;
    this->Draw = TAnimatedSprite_Draw;
    this->file = strdup(file);
    this->size = size;
    this->pos = pos;
    this->speed = speed;
    this->actual_frame = 0;
    SDL_QueryTexture(this->texture, NULL, NULL, &w, &h);
    this->len_frames = w / size.w;
    this->last_time = 0;
    this->animations = animations;
    this->is_visible = 1;
}

void TAnimatedSprite_Draw(TAnimatedSprite *this, TFrame *frame)
{
    if (!this || !frame || !this->texture) return;

    SDL_Rect tmp_frame = {this->size.w * this->actual_frame, this->size.y, this->size.w, this->size.h};
    unsigned int current_time = 0;

    current_time = SDL_GetTicks();
    if (current_time > this->last_time + this->speed && this->animations != 0) {
        this->actual_frame = (this->actual_frame + 1) % this->len_frames;
        this->last_time = current_time;
        if (this->actual_frame == 0 && this->animations > 0)
            (this->animations)--;
    }
    if (this->animations != 0)
        SDL_RenderCopy(frame->window->renderer_window, this->texture, &tmp_frame, &this->pos);
    else
        frame->Free_Drawable_Obj(frame, (TDrawable*)this);
}

void TAnimatedSprite_New_Free(TAnimatedSprite *this)
{
    if (this) {
        if (this->file)
            free(this->file);
        if (this->texture)
            SDL_DestroyTexture(this->texture);
    }
    free(this);
}

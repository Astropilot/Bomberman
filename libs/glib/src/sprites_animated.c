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
#include <SDL2/SDL_image.h>

#include "sprites_animated.h"
#include "scene.h"
#include "window.h"
#include "resource.h"

static void TAnimatedSprites_Init(TAnimatedSprites *this, TScene *scene, const char *file_template, size_t files, SDL_Rect size, SDL_Rect pos, size_t speed, int animations);

TAnimatedSprites* New_TAnimatedSprites(TScene *scene, const char *file_template, size_t files, SDL_Rect size, SDL_Rect pos, size_t speed, int animations)
{
    TAnimatedSprites *this = malloc(sizeof(TAnimatedSprites));

    if(!this) return (NULL);
    TAnimatedSprites_Init(this, scene, file_template, files, size, pos, speed, animations);
    this->Free = TAnimatedSprites_New_Free;
    return (this);
}

static void TAnimatedSprites_Init(TAnimatedSprites *this, TScene *scene, const char *file_template, size_t files, SDL_Rect size, SDL_Rect pos, size_t speed, int animations)
{
    if (!this || !scene || !file_template) return;

    this->Draw = TAnimatedSprites_Draw;
    this->file_template = strdup(file_template);
    this->size = size;
    this->pos = pos;
    this->speed = speed;
    this->actual_image = 0;
    this->nb_images = files;
    this->last_time = 0;
    this->animations = animations;

    this->textures = malloc(sizeof(SDL_Texture*) * this->nb_images);
    if (!this->textures) return;
    size_t i;
    TResourceCache *cache = scene->window->cache_manager;

    for (i = 0; i < this->nb_images; i++) {
        char file_path[128];

        sprintf(file_path, this->file_template, i);
        this->textures[i] = (SDL_Texture*)cache->FetchResource(cache, file_path, GRAPHICAL);
    }
    this->is_visible = 1;
}

void TAnimatedSprites_Draw(TAnimatedSprites *this, TScene *scene)
{
    if (!this || !scene || !this->textures) return;
    if (!this->is_visible) return;

    unsigned int current_time = 0;

    if (this->animations != 0)
        if (this->textures[this->actual_image])
            SDL_RenderCopy(scene->window->renderer_window, this->textures[this->actual_image], &this->size, &this->pos);
    current_time = SDL_GetTicks();
    if (current_time > this->last_time + this->speed && this->animations != 0) {
        this->actual_image = (this->actual_image + 1) % this->nb_images;
        this->last_time = current_time;
        if (this->actual_image == 0 && this->animations > 0)
            (this->animations)--;
    }
    if (this->animations == 0 && scene->Free_Drawable_Obj)
        scene->Free_Drawable_Obj(scene, (TDrawable*)this);
}

void TAnimatedSprites_New_Free(TAnimatedSprites *this)
{
    if (this) {
        size_t i;

        for (i = 0; i < this->nb_images; i++) {
            if (this->textures[i])
                SDL_DestroyTexture(this->textures[i]);
        }
        free(this->textures);
        free(this->file_template);
    }
    free(this);
}

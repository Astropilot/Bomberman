/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Source file of the animated sprites component of GLib.
*/

#include <stdio.h>

#include "sprites_animated.h"
#include "frame.h"
#include "window.h"

static void TAnimatedSprites_Init(TAnimatedSprites *this, TFrame *frame, const char *file_template, size_t files, SDL_Rect size, SDL_Rect pos, size_t speed, int animations);

TAnimatedSprites* New_TAnimatedSprites(TFrame *frame, const char *file_template, size_t files, SDL_Rect size, SDL_Rect pos, size_t speed, int animations)
{
    TAnimatedSprites *this = malloc(sizeof(TAnimatedSprites));

    if(!this) return NULL;
    TAnimatedSprites_Init(this, frame, file_template, files, size, pos, speed, animations);
    this->Free = TAnimatedSprites_New_Free;
    return this;
}

static void TAnimatedSprites_Init(TAnimatedSprites *this, TFrame *frame, const char *file_template, size_t files, SDL_Rect size, SDL_Rect pos, size_t speed, int animations)
{
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
    size_t i;

    for (i = 0; i < this->nb_images; i++) {
        char file_path[128];
        SDL_Surface *surface = NULL;

        sprintf(file_path, this->file_template, i);
        surface = IMG_Load(file_path);
        this->textures[i] = SDL_CreateTextureFromSurface(frame->window->renderer_window, surface);

        SDL_FreeSurface(surface);
    }
    this->is_visible = 1;
}

void TAnimatedSprites_Draw(TAnimatedSprites *this, TFrame *frame)
{
    if (!this || !frame)
        return;

    unsigned int current_time = 0;

    if (this->animations != 0)
        SDL_RenderCopy(frame->window->renderer_window, this->textures[this->actual_image], &this->size, &this->pos);
    current_time = SDL_GetTicks();
    if (current_time > this->last_time + this->speed && this->animations != 0) {
        this->actual_image = (this->actual_image + 1) % this->nb_images;
        this->last_time = current_time;
        if (this->actual_image == 0 && this->animations > 0)
            (this->animations)--;
    }
}

void TAnimatedSprites_New_Free(TAnimatedSprites *this)
{
    if (this) {
        size_t i;

        for (i = 0; i < this->nb_images; i++) {
            SDL_DestroyTexture(this->textures[i]);
        }
        free(this->textures);
        free(this->file_template);
    }
    free(this);
    printf("Animated Sprites Free called!\n");
}

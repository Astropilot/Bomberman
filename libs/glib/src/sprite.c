/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Source file of the sprite component of GLib.
*/

#include <string.h>

#include "sprite.h"
#include "frame.h"
#include "window.h"

static void TSprite_Init(TSprite *this, TFrame *frame, const char *file, SDL_Rect pos);

TSprite* New_TSprite(TFrame *frame, const char *file, SDL_Rect pos)
{
    TSprite *this = malloc(sizeof(TSprite));

    if(!this) return NULL;
    TSprite_Init(this, frame, file, pos);
    this->Free = TSprite_New_Free;
    return this;
}

static void TSprite_Init(TSprite *this, TFrame *frame, const char *file, SDL_Rect pos)
{
    SDL_Surface *surface = IMG_Load(file);

    this->Draw = TSprite_Draw;
    this->file = strdup(file);
    this->pos = pos;
    this->texture = SDL_CreateTextureFromSurface(frame->window->renderer_window, surface);
    this->is_visible = 1;
    SDL_FreeSurface(surface);
}

void TSprite_Draw(TSprite *this, TFrame *frame)
{
    if (!this || !frame)
        return;

    SDL_RenderCopy(frame->window->renderer_window, this->texture, NULL, &this->pos);
}

void TSprite_New_Free(TSprite *this)
{
    if (this) {
        free(this->file);
        SDL_DestroyTexture(this->texture);
    }
    free(this);
}

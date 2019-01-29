/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Source file of the sprite component of GLib.
*/

#include "window.h"
#include "sprite.h"

static void TSprite_Init(TSprite *this, TWindow *win, const char *file, SDL_Rect pos);

TSprite* New_TSprite(TWindow *win, const char *file, SDL_Rect pos)
{
    TSprite *this = malloc(sizeof(TSprite));

    if(!this) return NULL;
    TSprite_Init(this, win, file, pos);
    this->Free = TSprite_New_Free;
    return this;
}

static void TSprite_Init(TSprite *this, TWindow *win, const char *file, SDL_Rect pos)
{
    SDL_Surface *surface = IMG_Load(file);

    this->Draw = TSprite_Draw;
    this->file = strdup(file);
    this->pos = pos;
    this->texture = SDL_CreateTextureFromSurface(win->renderer_window, surface);
    SDL_FreeSurface(surface);
}

void TSprite_Draw(TSprite *this, TWindow *win)
{
    SDL_RenderCopy(win->renderer_window, this->texture, NULL, &this->pos);
}

void TSprite_New_Free(TSprite *this)
{
    if (this) {
        free(this->file);
        SDL_DestroyTexture(this->texture);
    }
    free(this);
    printf("Sprite Free called!\n");
}

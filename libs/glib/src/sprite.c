#include "window.h"
#include "sprite.h"

static void TSprite_Init(TSprite *this, TWindow *win, const char *file, SDL_Rect size);

TSprite* New_TSprite(TWindow *win, const char *file, SDL_Rect size)
{
    TSprite *this = malloc(sizeof(TSprite));

    if(!this) return NULL;
    TSprite_Init(this, win, file, size);
    this->Free = TSprite_New_Free;
    return this;
}

static void TSprite_Init(TSprite *this, TWindow *win, const char *file, SDL_Rect size)
{
    SDL_Surface *surface = IMG_Load(file);

    this->Draw = TSprite_Draw;
    this->file = strdup(file);
    this->pos = size;
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

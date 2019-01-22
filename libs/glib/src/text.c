#include "window.h"
#include "text.h"

static void TText_Init(TText *this, const char *text, TWindow *win, TTF_Font *font, SDL_Color color, SDL_Rect pos);

TText* New_TText(const char *text, TWindow *win, TTF_Font *font, SDL_Color color, SDL_Rect pos)
{
    TText *this = malloc(sizeof(TText));

    if(!this) return NULL;
    TText_Init(this, text, win, font, color, pos);
    this->Free = TText_New_Free;
    return this;
}

static void TText_Init(TText *this, const char *text, TWindow *win, TTF_Font *font, SDL_Color color, SDL_Rect pos)
{
    this->Draw = TText_Draw;
    this->text = strdup(text);
    this->pos = pos;
    this->texture = createText(this->text, font, color, &this->pos, win);
}

void TText_Draw(TText *this, TWindow *win)
{
    SDL_RenderCopy(win->renderer_window, this->texture, NULL, &this->pos);
}

void TText_New_Free(TText *this)
{
    if (this) {
        free(this->text);
        SDL_DestroyTexture(this->texture);
    }
    free(this);
    printf("Text Free called!\n");
}

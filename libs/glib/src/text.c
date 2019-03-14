/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Source file of the text component of GLib.
*/

#include "text.h"
#include "frame.h"
#include "window.h"

static void TText_Init(TText *this, TFrame *frame, const char *text, TTF_Font *font, SDL_Color color, SDL_Rect pos);

TText* New_TText(TFrame *frame, const char *text, TTF_Font *font, SDL_Color color, SDL_Rect pos)
{
    TText *this = malloc(sizeof(TText));

    if(!this) return NULL;
    TText_Init(this, frame, text, font, color, pos);
    this->Free = TText_New_Free;
    return this;
}

static void TText_Init(TText *this, TFrame *frame, const char *text, TTF_Font *font, SDL_Color color, SDL_Rect pos)
{
    this->Draw = TText_Draw;
    this->text = strdup(text);
    this->pos = pos;
    this->texture = createText(frame, this->text, font, color, &this->pos);
    this->is_visible = 1;
}

void TText_Draw(TText *this, TFrame *frame)
{
    if (!this || !frame)
        return;

    SDL_RenderCopy(frame->window->renderer_window, this->texture, NULL, &this->pos);
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

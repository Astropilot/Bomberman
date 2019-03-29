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
#include <SDL2/SDL_ttf.h>

#include "text.h"
#include "frame.h"
#include "window.h"
#include "utils.h"

static void TText_Init(TText *this, TFrame *frame, const char *text, TTF_Font *font, SDL_Color color, SDL_Rect pos);

TText* New_TText(TFrame *frame, const char *text, TTF_Font *font, SDL_Color color, SDL_Rect pos)
{
    TText *this = malloc(sizeof(TText));

    if(!this) return (NULL);
    TText_Init(this, frame, text, font, color, pos);
    this->Free = TText_New_Free;
    return (this);
}

static void TText_Init(TText *this, TFrame *frame, const char *text, TTF_Font *font, SDL_Color color, SDL_Rect pos)
{
    if (!this || !frame || !text || !font) return;

    this->Draw = TText_Draw;
    this->Change_Text = TText_Change_Text;
    this->text = strdup(text);
    this->pos = pos;
    this->font = font;
    this->color = color;
    this->texture = createText(frame, this->text, font, color, &this->pos);
    this->is_visible = 1;
}

void TText_Draw(TText *this, TFrame *frame)
{
    if (!this || !frame || !this->texture) return;

    SDL_RenderCopy(frame->window->renderer_window, this->texture, NULL, &this->pos);
}

void TText_Change_Text(TText *this, TFrame *frame, const char *text)
{
    if (!this || !frame || !text) return;

    free(this->text);
    SDL_DestroyTexture(this->texture);

    this->text = strdup(text);
    this->texture = createText(frame, this->text, this->font, this->color, &this->pos);
}

void TText_New_Free(TText *this)
{
    if (this) {
        free(this->text);
        if (this->texture)
            SDL_DestroyTexture(this->texture);
        if (this->font)
            TTF_CloseFont(this->font);
    }
    free(this);
}

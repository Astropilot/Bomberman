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

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

#include "inputbox.h"
#include "frame.h"
#include "window.h"

static void TInput_Init(
    TInput *this, TFrame *frame, TSprite *input_sprite,
    SDL_Color color, size_t len, const char *placeholder, TTF_Font *font
);

TInput* New_TInput(
    TFrame *frame, TSprite *input_sprite,
    SDL_Color color, size_t len, const char *placeholder, TTF_Font *font
)
{
    TInput *this = malloc(sizeof(TInput));

    if(!this) return (NULL);
    TInput_Init(this, frame, input_sprite, color, len, placeholder, font);
    this->Free = TInput_New_Free;
    return (this);
}

static void TInput_Init(
    TInput *this, TFrame *frame, TSprite *input_sprite,
    SDL_Color color, size_t len, const char *placeholder, TTF_Font *font
)
{
    SDL_Surface *s_tmp;
    SDL_Rect pos;

    if (!this || !frame || !input_sprite) return;

    this->Draw = TInput_Draw;
    this->Event_Handler = TInput_Event_Handler;
    this->text = malloc(sizeof(char) * (len + 1));
    if (this->text)
        this->text[0] = '\0';
    if (placeholder)
        this->placeholder = strdup(placeholder);
    else
        this->placeholder = NULL;
    this->input_sprite = input_sprite;
    this->font = font;
    this->color = color;
    s_tmp = TTF_RenderText_Solid(this->font, "TmP", this->color);
    pos = input_sprite->pos;
    pos.x += 40;
    pos.y = ( (pos.y + pos.h) / 2) - ( (s_tmp->h - pos.y) / 2);
    this->pos_text = pos;
    this->is_focus = 0;
    this->last_time = 0;
    this->max_len = len;
    this->is_visible = 1;
    SDL_FreeSurface(s_tmp);
}

void TInput_Draw(TInput *this, TFrame *frame)
{
    if (!this || !frame || !this->text || !this->input_sprite) return;

    SDL_Texture *text_texture = NULL;
    unsigned int current_time = 0;
    SDL_Color color = {189, 189, 189, 255};

    if (this->input_sprite->Draw)
        this->input_sprite->Draw(this->input_sprite, frame);
    if (this->text[0] != '\0')
        text_texture = createText(frame, this->text, this->font, this->color, &this->pos_text);
    else if (this->placeholder)
        text_texture = createText(frame, this->placeholder, this->font, color, &this->pos_text);
    if (text_texture) {
        SDL_RenderCopy(frame->window->renderer_window, text_texture, NULL, &this->pos_text);
        SDL_DestroyTexture(text_texture);
    }
    if (!text_texture || (this->text[0] == '\0')) {
        this->pos_text.w = 0;
        this->pos_text.h = 0;
    }
    current_time = SDL_GetTicks();
    if (this->is_focus && (current_time > this->last_time + 500)) {
        SDL_Texture *cursor_texture = NULL;
        SDL_Rect pos_cursor = {
            (this->pos_text.x + this->pos_text.w) + 2, this->pos_text.y, 0, 0};

        cursor_texture = createText(frame, "_", this->font, this->color, &pos_cursor);
        if (cursor_texture) {
            SDL_RenderCopy(frame->window->renderer_window, cursor_texture, NULL, &pos_cursor);
            SDL_DestroyTexture(cursor_texture);
        }
        this->last_time = current_time;
    }
}

void TInput_Event_Handler(TInput *this, SDL_Event event)
{
    if (!this || !this->text) return;

    SDL_Rect pos_input = this->input_sprite->pos;

    if( event.type == SDL_MOUSEBUTTONUP ) {
        int x;
        int y;

        SDL_GetMouseState( &x, &y );
        if (x >= pos_input.x && x <= (pos_input.x + pos_input.w))
            if (y >= pos_input.y && y <= (pos_input.y + pos_input.h))
                this->is_focus = 1;
            else
                this->is_focus = 0;
        else
            this->is_focus = 0;
    }

    if (!this->is_focus)
        return;
    if (event.type == SDL_TEXTINPUT) {
        if( !(SDL_GetModState() & KMOD_CTRL) ) {
            size_t text_len = strlen(this->text);
            size_t new_text_len = strlen(event.text.text);

            if ( (text_len + new_text_len) <= this->max_len)
                strcat(this->text, event.text.text);
        }
    } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_BACKSPACE) {
            size_t text_len = strlen(this->text);

            if (text_len > 0) {
                this->text[text_len - 1] = '\0';
            }
        }
    }
}

void TInput_New_Free(TInput *this)
{
    if (this) {
        if (this->input_sprite && this->input_sprite->Free)
            this->input_sprite->Free(this->input_sprite);
        free(this->text);
        free(this->placeholder);
        if (this->font)
            TTF_CloseFont(this->font);
    }
    free(this);
}

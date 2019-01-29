/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Source file for the input box component of GLib.
*/

#include "inputbox.h"

static void TInput_Init(TInput *this, const char *file, SDL_Rect pos, TWindow *win, SDL_Color color);

TInput* New_TInput(const char *sprite_file, SDL_Rect pos, TWindow *window, SDL_Color color)
{
    TInput *this = malloc(sizeof(TInput));

    if(!this) return NULL;
    TInput_Init(this, sprite_file, pos, window, color);
    this->Free = TInput_New_Free;
    return this;
}

static void TInput_Init(TInput *this, const char *file, SDL_Rect pos, TWindow *win, SDL_Color color)
{
    SDL_Surface *s_tmp;

    this->Draw = TInput_Draw;
    this->Event_Handler = TInput_Event_Handler;
    strcpy(this->text, "");
    this->input_sprite = New_TSprite(win, file, pos);
    this->font = TTF_OpenFont("fonts/fixedsys.ttf", 24);
    this->color = color;
    this->pos_input = pos;
    s_tmp = TTF_RenderText_Solid(this->font, "TmP", this->color);
    pos.x += 40;
    pos.y = ( (pos.y + pos.h) / 2) - ( (s_tmp->h - pos.y) / 2);
    this->pos_text = pos;
    this->is_focus = 0;
    this->last_time = 0;
    free(s_tmp);
}

void TInput_Draw(TInput *this, TWindow *window)
{
    unsigned int current_time = 0;

    this->input_sprite->Draw(this->input_sprite, window);
    this->pos_text.w = 0;
    this->pos_text.h = 0;
    if (strlen(this->text) > 0) {
        SDL_Texture *text_texture = NULL;

        text_texture = createText(this->text, this->font, this->color, &this->pos_text, window);
        SDL_RenderCopy(window->renderer_window, text_texture, NULL, &this->pos_text);
        SDL_DestroyTexture(text_texture);
    }
    current_time = SDL_GetTicks();
    if (this->is_focus && (current_time > this->last_time + 500)) {
        SDL_Texture *cursor_texture = NULL;
        SDL_Rect pos_cursor = {
            (this->pos_text.x + this->pos_text.w) + 2, this->pos_text.y, 0, 0};

        cursor_texture = createText("_", this->font, this->color, &pos_cursor, window);
        SDL_RenderCopy(window->renderer_window, cursor_texture, NULL, &pos_cursor);
        SDL_DestroyTexture(cursor_texture);
        this->last_time = current_time;
    }
}

void TInput_Event_Handler(TInput *this, TWindow *win, SDL_Event event)
{
    if( event.type == SDL_MOUSEBUTTONUP ) {
        int x;
        int y;

        SDL_GetMouseState( &x, &y );
        if (x >= this->pos_input.x && x <= (this->pos_input.x + this->pos_input.w))
            if (y >= this->pos_input.y && y <= (this->pos_input.y + this->pos_input.h))
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
            unsigned int text_len = strlen(this->text);
            unsigned int new_text_len = strlen(event.text.text);

            if ( (text_len + new_text_len) < MAX_STR_LEN - 1)
                strcat(this->text, event.text.text);
            printf("Input event %p\n", win);
        }
    } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_BACKSPACE) {
            unsigned int text_len = strlen(this->text);

            if (text_len > 0) {
                this->text[text_len - 1] = '\0';
            }
        }
    }
}

void TInput_New_Free(TInput *this)
{
    if (this) {
        this->input_sprite->Free(this->input_sprite);
        TTF_CloseFont(this->font);
    }
    free(this);
    printf("Input Free called!\n");
}

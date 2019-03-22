/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Source file of the button component of GLib.
*/

#include "button.h"
#include "frame.h"
#include "window.h"

static void TButton_Init(TButton *this, TFrame *frame, const char *btn_s, const char *btn_hs, SDL_Rect pos);

TButton* New_TButton(TFrame *frame, const char *btn_s, const char *btn_hs, SDL_Rect pos)
{
    TButton *this = malloc(sizeof(TButton));

    if(!this) return NULL;
    TButton_Init(this, frame, btn_s, btn_hs, pos);
    this->Free = TButton_New_Free;
    return this;
}

static void TButton_Init(TButton *this, TFrame *frame, const char *btn_s, const char *btn_hs, SDL_Rect pos)
{
    this->Draw = TButton_Draw;
    this->Event_Handler = TButton_Event_Handler;
    this->btn_sprite = New_TSprite(frame, btn_s, pos);
    this->btn_hover_sprite = New_TSprite(frame, btn_hs, pos);
    this->state = BUTTON_NORMAL;
    this->pos = pos;
    this->is_visible = 1;
}


void TButton_Draw(TButton *this, TFrame *frame)
{
    if (!this || !frame)
        return;

    this->btn_sprite->pos = this->pos;
    this->btn_hover_sprite->pos = this->pos;

    switch (this->state) {
        case BUTTON_NORMAL:
            this->btn_sprite->Draw(this->btn_sprite, frame);
            break;
        case BUTTON_HOVER:
            this->btn_hover_sprite->Draw(this->btn_hover_sprite, frame);
    }
}

void TButton_Event_Handler(TButton *this, TFrame *frame, SDL_Event event)
{
    if (!this || !frame)
        return;

    if( event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONUP ) {
        int x;
        int y;
        this->state = BUTTON_NORMAL;

        SDL_GetMouseState( &x, &y );
        if (x >= this->pos.x && x <= (this->pos.x + this->pos.w))
            if (y >= this->pos.y && y <= (this->pos.y + this->pos.h))
                this->state = BUTTON_HOVER;
        if (event.type == SDL_MOUSEBUTTONUP && this->state == BUTTON_HOVER)
            this->On_Click(this, frame);
    }
}

void TButton_New_Free(TButton *this)
{
    if (this) {
        this->btn_sprite->Free(this->btn_sprite);
        this->btn_hover_sprite->Free(this->btn_hover_sprite);
    }
    free(this);
    printf("Button Free called!\n");
}

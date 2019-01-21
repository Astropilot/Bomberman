#include "button.h"

static void TButton_Init(TButton *this, const char *btn_s, const char *btn_hs, SDL_Rect pos, TWindow *win);

TButton* New_TButton(const char *btn_s, const char *btn_hs, SDL_Rect pos, TWindow *win)
{
    TButton *this = malloc(sizeof(TButton));

    if(!this) return NULL;
    TButton_Init(this, btn_s, btn_hs, pos, win);
    this->Free = TButton_New_Free;
    return this;
}

static void TButton_Init(TButton *this, const char *btn_s, const char *btn_hs, SDL_Rect pos, TWindow *win)
{
    this->Draw = TButton_Draw;
    this->Event_Handler = TButton_Event_Handler;
    this->btn_sprite = New_TSprite("BTN", win, btn_s, pos);
    this->btn_hover_sprite = New_TSprite("BTN_HOVER", win, btn_hs, pos);
    this->state = BUTTON_NORMAL;
    this->pos = pos;
}

void TButton_Draw(TButton *this, TWindow *window)
{
    this->btn_sprite->pos = this->pos;
    this->btn_hover_sprite->pos = this->pos;

    switch (this->state) {
        case BUTTON_NORMAL:
            this->btn_sprite->Draw(this->btn_sprite, window);
            break;
        case BUTTON_HOVER:
            this->btn_hover_sprite->Draw(this->btn_hover_sprite, window);
    }
}

void TButton_Event_Handler(TButton *this, TWindow *win, SDL_Event event)
{
    if( event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONUP ) {
        int x;
        int y;
        this->state = BUTTON_NORMAL;

        SDL_GetMouseState( &x, &y );
        if (x >= this->pos.x && x <= (this->pos.x + this->pos.w))
            if (y >= this->pos.y && y <= (this->pos.y + this->pos.h))
                this->state = BUTTON_HOVER;
        if (event.type == SDL_MOUSEBUTTONUP && this->state == BUTTON_HOVER)
            this->On_Click(this, win);
    }
}

void TButton_New_Free(TButton *this)
{
    if (this) {
        this->btn_sprite->Free(this->btn_sprite);
        this->btn_hover_sprite->Free(this->btn_hover_sprite);
    }
    free(this);
}

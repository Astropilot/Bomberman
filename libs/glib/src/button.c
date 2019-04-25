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

#include "button.h"
#include "scene.h"

static void TButton_Init(TButton *this, TScene *scene, const char *btn_s, const char *btn_hs, SDL_Rect pos);

TButton* New_TButton(TScene *scene, const char *btn_s, const char *btn_hs, SDL_Rect pos)
{
    TButton *this = malloc(sizeof(TButton));

    if(!this) return (NULL);
    TButton_Init(this, scene, btn_s, btn_hs, pos);
    this->Free = TButton_New_Free;
    return (this);
}

static void TButton_Init(TButton *this, TScene *scene, const char *btn_s, const char *btn_hs, SDL_Rect pos)
{
    if (!this || !scene || !btn_s || !btn_hs) return;

    this->Draw = TButton_Draw;
    this->Event_Handler = TButton_Event_Handler;
    this->btn_sprite = New_TSprite(scene, btn_s, pos);
    this->btn_hover_sprite = New_TSprite(scene, btn_hs, pos);
    this->state = BUTTON_NORMAL;
    this->pos = pos;
    this->is_visible = 1;
}


void TButton_Draw(TButton *this, TScene *scene)
{
    if (!this || !scene || !this->btn_sprite || !this->btn_hover_sprite) return;
    if (!this->is_visible) return;

    this->btn_sprite->pos = this->pos;
    this->btn_hover_sprite->pos = this->pos;

    switch (this->state) {
        case BUTTON_NORMAL:
            this->btn_sprite->Draw(this->btn_sprite, scene);
            break;
        case BUTTON_HOVER:
            this->btn_hover_sprite->Draw(this->btn_hover_sprite, scene);
    }
}

void TButton_Event_Handler(TButton *this, TScene *scene, SDL_Event event)
{
    if (!this || !scene) return;
    if (!this->is_visible) return;

    if( event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONUP ) {
        int x;
        int y;
        this->state = BUTTON_NORMAL;

        SDL_GetMouseState( &x, &y );
        if (x >= this->pos.x && x <= (this->pos.x + this->pos.w))
            if (y >= this->pos.y && y <= (this->pos.y + this->pos.h))
                this->state = BUTTON_HOVER;
        if (event.type == SDL_MOUSEBUTTONUP && this->state == BUTTON_HOVER)
            if (this->On_Click)
                this->On_Click(this, scene);
    }
}

void TButton_New_Free(TButton *this)
{
    if (this) {
        if (this->btn_sprite && this->btn_sprite->Free)
            this->btn_sprite->Free(this->btn_sprite);
        if (this->btn_hover_sprite && this->btn_hover_sprite->Free)
            this->btn_hover_sprite->Free(this->btn_hover_sprite);
    }
    free(this);
}

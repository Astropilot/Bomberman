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

#include <math.h>
#include <SDL2/SDL.h>

#include "slider.h"
#include "scene.h"

static void TSlider_Init(
    TSlider *this, TScene *scene, const char *bg_s, const char *btn_s,
    SDL_Rect pos, SDL_Point btn_size, int min_val, int max_val, int value
);

TSlider* New_TSlider(
    TScene *scene, const char *bg_s, const char *btn_s,
    SDL_Rect pos, SDL_Point btn_size, int min_val, int max_val, int value
)
{
    TSlider *this = malloc(sizeof(TSlider));

    if(!this) return (NULL);
    TSlider_Init(this, scene, bg_s, btn_s, pos, btn_size, min_val, max_val, value);
    this->Free = TSlider_New_Free;
    return (this);
}

static void TSlider_Init(
    TSlider *this, TScene *scene, const char *bg_s, const char *btn_s,
    SDL_Rect pos, SDL_Point btn_size, int min_val, int max_val, int value
)
{
    if (!this || !scene || !bg_s || !btn_s) return;
    SDL_Rect pos_cp = pos;

    this->Draw = TSlider_Draw;
    this->Event_Handler = TSlider_Event_Handler;
    this->sprite_bg = New_TSprite(scene, bg_s, pos);
    pos_cp.w = btn_size.x;
    pos_cp.h = btn_size.y;
    this->sprite_btn = New_TSprite(scene, btn_s, pos_cp);
    if (value < min_val || value > max_val)
        this->value = min_val;
    this->value = value;
    this->min_value = min_val;
    this->max_value = max_val;
    this->pos = pos;
    this->btn_size = btn_size;
    this->is_visible = 1;
    this->lclick_pressed = 0;
}


void TSlider_Draw(TSlider *this, TScene *scene)
{
    if (!this || !scene || !this->sprite_bg || !this->sprite_btn) return;
    if (!this->is_visible) return;

    SDL_Rect pos_btn = this->pos;
    int delta;

    this->sprite_bg->pos = this->pos;

    delta = this->pos.w / (this->max_value - this->min_value);

    pos_btn.x += (this->value - this->min_value) * delta;
    pos_btn.w = this->btn_size.x;
    pos_btn.h = this->btn_size.y;

    this->sprite_btn->pos = pos_btn;

    this->sprite_bg->Draw(this->sprite_bg, scene);
    this->sprite_btn->Draw(this->sprite_btn, scene);
}

void TSlider_Event_Handler(TSlider *this, TScene *scene, SDL_Event event)
{
    if (!this || !scene) return;
    if (!this->is_visible) return;

    if (event.type == SDL_MOUSEBUTTONDOWN)
        this->lclick_pressed = 1;
    if (event.type == SDL_MOUSEBUTTONUP)
        this->lclick_pressed = 0;
    if ((event.type == SDL_MOUSEMOTION && this->lclick_pressed) || event.type == SDL_MOUSEBUTTONUP) {
        int x;
        int y;

        SDL_GetMouseState( &x, &y );
        if (x >= this->pos.x && x <= (this->pos.x + this->pos.w)) {
            if (y >= this->pos.y && y <= (this->pos.y + this->pos.h)) {
                double delta;
                double delta2;
                int prev_value = this->value;

                delta = (double)this->pos.w / (double)(this->max_value - this->min_value);
                delta2 = (double)x - (double)this->pos.x;
                delta2 = round(delta2 / delta);

                this->value = this->min_value + (int)delta2;

                if (this->value != prev_value && this->On_ValueChange)
                    this->On_ValueChange(this, scene, this->value);
            }
        }
    }
}

void TSlider_New_Free(TSlider *this)
{
    if (this) {
        if (this->sprite_bg && this->sprite_bg->Free)
            this->sprite_bg->Free(this->sprite_bg);
        if (this->sprite_btn && this->sprite_btn->Free)
            this->sprite_btn->Free(this->sprite_btn);
    }
    free(this);
}

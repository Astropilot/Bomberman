/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Source file of the animated sprite component of GLib.
*/

#include "sprite_animated.h"
#include "frame.h"
#include "window.h"

static void TAnimatedSprite_Init(TAnimatedSprite *this, TFrame *frame, const char *file, SDL_Rect size, SDL_Rect pos, size_t speed, int animations);

TAnimatedSprite* New_TAnimatedSprite(TFrame *frame, const char *file, SDL_Rect size, SDL_Rect pos, size_t speed, int animations)
{
    TAnimatedSprite *this = malloc(sizeof(TAnimatedSprite));

    if(!this) return NULL;
    TAnimatedSprite_Init(this, frame, file, size, pos, speed, animations);
    this->Free = TAnimatedSprite_New_Free;
    return this;
}

static void TAnimatedSprite_Init(TAnimatedSprite *this, TFrame *frame, const char *file, SDL_Rect size, SDL_Rect pos, size_t speed, int animations)
{
    SDL_Surface *surface = IMG_Load(file);
    int w, h;

    this->Draw = TAnimatedSprite_Draw;
    this->file = strdup(file);
    this->size = size;
    this->pos = pos;
    this->speed = speed;
    this->actual_frame = 0;
    this->texture = SDL_CreateTextureFromSurface(frame->window->renderer_window, surface);
    SDL_QueryTexture(this->texture, NULL, NULL, &w, &h);
    this->len_frames = w / size.w;
    this->last_time = 0;
    this->animations = animations;
    this->is_visible = 1;
    SDL_FreeSurface(surface);
}

void TAnimatedSprite_Draw(TAnimatedSprite *this, TFrame *frame)
{
    if (!this || !frame)
        return;

    SDL_Rect tmp_frame = {this->size.w * this->actual_frame, this->size.y, this->size.w, this->size.h};
    unsigned int current_time = 0;

    current_time = SDL_GetTicks();
    if (current_time > this->last_time + this->speed && this->animations != 0) {
        this->actual_frame = (this->actual_frame + 1) % this->len_frames;
        this->last_time = current_time;
        if (this->actual_frame == 0 && this->animations > 0)
            (this->animations)--;
    }
    if (this->animations != 0)
        SDL_RenderCopy(frame->window->renderer_window, this->texture, &tmp_frame, &this->pos);
    else
        frame->Free_Drawable_Obj(frame, (TDrawable*)this);
}

void TAnimatedSprite_New_Free(TAnimatedSprite *this)
{
    if (this) {
        free(this->file);
        SDL_DestroyTexture(this->texture);
    }
    free(this);
    printf("Animated Sprite Free called!\n");
}

#include "window.h"
#include "sprite_animated.h"

static void TAnimatedSprite_Init(TAnimatedSprite *this, TWindow *win, const char *file, SDL_Rect size, SDL_Rect pos, size_t speed);

TAnimatedSprite* New_TAnimatedSprite(TWindow *win, const char *file, SDL_Rect size, SDL_Rect pos, size_t speed)
{
    TAnimatedSprite *this = malloc(sizeof(TAnimatedSprite));

    if(!this) return NULL;
    TAnimatedSprite_Init(this, win, file, size, pos, speed);
    this->Free = TAnimatedSprite_New_Free;
    return this;
}

static void TAnimatedSprite_Init(TAnimatedSprite *this, TWindow *win, const char *file, SDL_Rect size, SDL_Rect pos, size_t speed)
{
    SDL_Surface *surface = IMG_Load(file);
    int w, h;

    this->Draw = TAnimatedSprite_Draw;
    this->file = strdup(file);
    this->size = size;
    this->pos = pos;
    this->speed = speed;
    this->actual_frame = 0;
    this->texture = SDL_CreateTextureFromSurface(win->renderer_window, surface);
    SDL_QueryTexture(this->texture, NULL, NULL, &w, &h);
    this->len_frames = w / size.w;
    this->last_time = 0;
    SDL_FreeSurface(surface);
}

void TAnimatedSprite_Draw(TAnimatedSprite *this, TWindow *win)
{
    SDL_Rect tmp_frame = {this->size.w * this->actual_frame, this->size.y, this->size.w, this->size.h};
    unsigned int current_time = 0;

    current_time = SDL_GetTicks();
    if (current_time > this->last_time + this->speed) {
        this->actual_frame = (this->actual_frame + 1) % this->len_frames;
        this->last_time = current_time;
    }
    SDL_RenderCopy(win->renderer_window, this->texture, &tmp_frame, &this->pos);
}

void TAnimatedSprite_New_Free(TAnimatedSprite *this)
{
    if (this) {
        free(this->file);
        SDL_DestroyTexture(this->texture);
    }
    free(this);
    printf("Sprite Free called!\n");
}

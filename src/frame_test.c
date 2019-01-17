#include "frame_test.h"

static void Init(TFrame* frame, TWindow *window);
static void On_Load(TFrame* frame, TWindow *window);
static void On_Event(TFrame* frame, TWindow *window, SDL_Event event);
static void On_Tick(TFrame* frame, TWindow *window);
static void Finish(TFrame* frame, TWindow *window);

static SDL_Texture *my_sprite = NULL;
static SDL_Rect pos_sprite = {0, 0, 0, 0};
static unsigned int sprite_speed = 1;

TFrame* New_TestFrame(void)
{
    TFrame *frm = New_TFrame("FRAME_TEST");
    frm->Init = Init;
    frm->On_Load = On_Load;
    frm->On_Event = On_Event;
    frm->On_Tick = On_Tick;
    frm->Finish = Finish;
    return (frm);
}

static void Init(TFrame* frame, TWindow *window)
{
    printf("Frame [%s]: Init method called | Window finished: %d\n", frame->frame_id, window->finished);
    my_sprite = create_texture("images/sprite.png", window);
    SDL_SetRenderDrawColor(window->renderer_window, 255, 0, 0, 255);
}

static void On_Load(TFrame* frame, TWindow *window)
{
    printf("Frame [%s]: On_Load method called | Window finished: %d\n", frame->frame_id, window->finished);
    pos_sprite.x = 0;
    pos_sprite.y = 0;
    pos_sprite.w = 24;
    pos_sprite.h = 24;
    SDL_RenderClear(window->renderer_window);
}

static void On_Event(TFrame* frame, TWindow *window, SDL_Event event)
{
    if (event.type == SDL_KEYDOWN) {
        printf("Frame [%s]: On_Event method called with SPACE KEY PRESSED | Window finished: %d\n", frame->frame_id, window->finished);

        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                pos_sprite.x -= sprite_speed;
                break;
            case SDLK_RIGHT:
                pos_sprite.x += sprite_speed;
                break;
            case SDLK_UP:
                pos_sprite.y -= sprite_speed;
                break;
            case SDLK_DOWN:
                pos_sprite.y += sprite_speed;
                break;
        }
    } else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_KP_PLUS)
            sprite_speed += 5;
        if (event.key.keysym.sym == SDLK_KP_MINUS)
            sprite_speed -= 5;
    }
}

static void On_Tick(TFrame* frame, TWindow *window)
{
    printf("Frame [%s]: On_Tick method called | Window finished: %d\n", frame->frame_id, window->finished);
    SDL_RenderClear(window->renderer_window);
    SDL_RenderCopy(window->renderer_window, my_sprite, NULL, &pos_sprite);
    SDL_RenderPresent(window->renderer_window);
}

static void Finish(TFrame* frame, TWindow *window)
{
    printf("Frame [%s]: Finish method called | Window finished: %d\n", frame->frame_id, window->finished);
    SDL_DestroyTexture(my_sprite);
}

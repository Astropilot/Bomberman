/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the game frame.
*/

#include "frame_game.h"
#include "main.h"

static void Init(TFrame *frame, TWindow *window);
static void On_Load(TFrame *frame, TWindow *window, va_list args);
static void On_Event(TFrame *frame, TWindow *window, SDL_Event event);
static void On_Tick(TFrame *frame, TWindow *window);
static void On_Unload(TFrame *frame, TWindow *window);
static void Finish(TFrame *frame, TWindow *window);

static unsigned int sprite_speed = 12;

TFrame* New_GameFrame(void)
{
    TFrame *frm = New_TFrame("FRAME_GAME");
    frm->Init = Init;
    frm->On_Load = On_Load;
    frm->On_Event = On_Event;
    frm->On_Tick = On_Tick;
    frm->On_Unload = On_Unload;
    frm->Finish = Finish;
    return (frm);
}

static void Init(TFrame* frame, TWindow *window)
{
    SDL_Rect pos_sprite2 = {0, 0, WIN_WIDTH, WIN_HEIGHT};
    TSprite *sp2 = New_TSprite(window, "images/bomberman_game.png", pos_sprite2);

    SDL_Rect pos_anim_sprite = {200, 223, 64, 64};
    SDL_Rect size_anim_sprite = {0, 0, 256, 256};
    TAnimatedSprite *asp = New_TAnimatedSprite(window, "images/sprite_animated.png", size_anim_sprite, pos_anim_sprite , 100, -1);

    frame->Add_Drawable(frame, (TDrawable*)sp2, "BG", 999);
    frame->Add_Drawable(frame, (TDrawable*)asp, "PLAYER", 1);
}

static void On_Load(TFrame* frame, TWindow *window, va_list args)
{
    char *username = va_arg(args, char*);
    TAnimatedSprite *asp = (TAnimatedSprite*)frame->Get_Drawable(frame, "PLAYER");
    SDL_Rect pos_username = {0, 0, 0, 0};
    SDL_Color color = {255, 255, 255, 255};

    TText *txt = New_TText(username, window, TTF_OpenFont("fonts/fixedsys.ttf", 24), color, pos_username);
    txt->pos.x = (WIN_WIDTH / 2) - (txt->pos.w / 2);
    txt->pos.y = 40;

    frame->Add_Drawable(frame, (TDrawable*)txt, "LABEL_USERNAME", 1);

    asp->pos.x = 200;
    asp->pos.y = 223;
    sprite_speed = 12;

    SDL_RenderClear(window->renderer_window);
}

static void On_Event(TFrame* frame, TWindow *window, SDL_Event event)
{
    if (event.type == SDL_KEYDOWN) {
        TAnimatedSprite *asp = (TAnimatedSprite *)frame->Get_Drawable(frame, "PLAYER");

        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                asp->pos.x -= sprite_speed;
                break;
            case SDLK_RIGHT:
                asp->pos.x += sprite_speed;
                break;
            case SDLK_UP:
                asp->pos.y -= sprite_speed;
                break;
            case SDLK_DOWN:
                asp->pos.y += sprite_speed;
                break;
        }
    } else if (event.type == SDL_KEYUP) {
        TAnimatedSprite *asp = (TAnimatedSprite *)frame->Get_Drawable(frame, "PLAYER");

        if (event.key.keysym.sym == SDLK_KP_PLUS)
            sprite_speed += 5;
        if (event.key.keysym.sym == SDLK_KP_MINUS)
            sprite_speed -= 5;
        if (event.key.keysym.sym == SDLK_ESCAPE)
            window->Show_Frame(window, "FRAME_MAIN_MENU", 0);
        if (event.key.keysym.sym == SDLK_SPACE) {
            SDL_Rect size_bomb = {0, 0, 256, 256};
            SDL_Rect pos_bomb = {asp->pos.x + (asp->pos.w / 2), asp->pos.y + (asp->pos.h / 2), 32, 32};
            TAnimatedSprite *sp = New_TAnimatedSprite(window, "images/bomberman_bomb_animated.png", size_bomb, pos_bomb, 128, 1);

            frame->Add_Drawable(frame, (TDrawable*)sp, "BOMB", 2);
        }
    }
}

static void On_Tick(TFrame* frame, TWindow *window)
{
    SDL_RenderClear(window->renderer_window);
    frame->Draw_Drawables(frame, window);
    SDL_RenderPresent(window->renderer_window);
}

static void On_Unload(TFrame* frame, TWindow *window)
{
    if (IS_DEBUG)
        printf("Frame [%s]: On_Unload method called | Window finished: %d\n", frame->frame_id, window->finished);

    TSprite *bomb_sprite = (TSprite*)frame->Remove_Drawable(frame, "BOMB");
    TText *txt_username = (TText*)frame->Remove_Drawable(frame, "LABEL_USERNAME");

    while (bomb_sprite) {
        bomb_sprite->Free(bomb_sprite);
        bomb_sprite = (TSprite*)frame->Remove_Drawable(frame, "BOMB");
    }
    txt_username->Free(txt_username);
}

static void Finish(TFrame* frame, TWindow *window)
{
    if (IS_DEBUG)
        printf("Frame [%s]: Finish method called | Window finished: %d\n", frame->frame_id, window->finished);
}

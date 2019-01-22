#include "frame_game.h"

static void Init(TFrame *frame, TWindow *window);
static void On_Load(TFrame *frame, TWindow *window, va_list args);
static void On_Event(TFrame *frame, TWindow *window, SDL_Event event);
static void On_Tick(TFrame *frame, TWindow *window);
static void On_Unload(TFrame *frame, TWindow *window);
static void Finish(TFrame *frame, TWindow *window);

static unsigned int sprite_speed = 32;

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
    printf("Frame [%s]: Init method called | Window finished: %d\n", frame->frame_id, window->finished);
    // Ajout dans la Frame pour une gestion automatique du dessin et de
    // la libération des ressources
    SDL_Rect pos_sprite = {120, 223, 24, 24};
    TSprite *sp = New_TSprite(window, "images/sprite.png", pos_sprite);

    SDL_Rect pos_sprite2 = {0, 0, 700, 800};
    TSprite *sp2 = New_TSprite(window, "images/bomberman_game.png", pos_sprite2);

    frame->Add_Drawable(frame, (void*)sp2, SPRITE, "BG", 999);
    frame->Add_Drawable(frame, (void*)sp, SPRITE, "ICO", 1);
}

static void On_Load(TFrame* frame, TWindow *window, va_list args)
{
    char *username = va_arg(args, char*);
    printf("Debug %p\n", &args);
    TSprite *sprite = (TSprite*)frame->Get_Drawable(frame, "ICO");
    SDL_Rect pos_username = {0, 0, 0, 0};
    SDL_Color color = {255, 255, 255, 255};

    TText *txt = New_TText(username, window, TTF_OpenFont("fonts/fixedsys.ttf", 24), color, pos_username);
    txt->pos.x = (700 / 2) - (txt->pos.w / 2);
    txt->pos.y = 40;

    frame->Add_Drawable(frame, (void*)txt, TEXT, "LABEL_USERNAME", 1);

    sprite->pos.x = 120;
    sprite->pos.y = 223;
    sprite_speed = 32;

    SDL_RenderClear(window->renderer_window);
}

static void On_Event(TFrame* frame, TWindow *window, SDL_Event event)
{
    if (event.type == SDL_KEYDOWN) {
        TSprite *sprite = (TSprite *)frame->Get_Drawable(frame, "ICO");

        printf("Frame [%s]: On_Event method called with key pressed | Window finished: %d\n", frame->frame_id, window->finished);
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                sprite->pos.x -= sprite_speed;
                break;
            case SDLK_RIGHT:
                sprite->pos.x += sprite_speed;
                break;
            case SDLK_UP:
                sprite->pos.y -= sprite_speed;
                break;
            case SDLK_DOWN:
                sprite->pos.y += sprite_speed;
                break;
        }
    } else if (event.type == SDL_KEYUP) {
        TSprite *sprite = (TSprite*)frame->Get_Drawable(frame, "ICO");

        if (event.key.keysym.sym == SDLK_KP_PLUS)
            sprite_speed += 5;
        if (event.key.keysym.sym == SDLK_KP_MINUS)
            sprite_speed -= 5;
        if (event.key.keysym.sym == SDLK_ESCAPE)
            window->Show_Frame(window, "FRAME_MENU", 0);
        if (event.key.keysym.sym == SDLK_SPACE) {
            SDL_Rect pos_bomb = {sprite->pos.x, sprite->pos.y, 24, 24};
            TSprite *sp = New_TSprite(window, "images/bomb.png", pos_bomb);

            frame->Add_Drawable(frame, (void*)sp, SPRITE, "BOMB", 2);
        }
    }
}

static void On_Tick(TFrame* frame, TWindow *window)
{
    printf("Frame [%s]: On_Tick method called: %d | Window finished: %d\n", frame->frame_id, frame->initialized, window->finished);
    SDL_RenderClear(window->renderer_window);
    frame->Draw_Drawables(frame, window);
    SDL_RenderPresent(window->renderer_window);
}

static void On_Unload(TFrame* frame, TWindow *window)
{
    TSprite *bomb_sprite = (TSprite*)frame->Remove_Drawable(frame, "BOMB");
    TText *txt_username = (TText*)frame->Remove_Drawable(frame, "LABEL_USERNAME");

    while (bomb_sprite) {
        bomb_sprite->Free(bomb_sprite);
        bomb_sprite = (TSprite*)frame->Remove_Drawable(frame, "BOMB");
    }
    txt_username->Free(txt_username);
    printf("Frame [%s]: On_Unload method called | Window finished: %d\n", frame->frame_id, window->finished);
}

static void Finish(TFrame* frame, TWindow *window)
{
    printf("Frame [%s]: Finish method called | Window finished: %d\n", frame->frame_id, window->finished);
}

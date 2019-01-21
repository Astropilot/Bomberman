#include "frame_game.h"

static void Init(TFrame *frame, TWindow *window);
static void On_Load(TFrame *frame, TWindow *window);
static void On_Event(TFrame *frame, TWindow *window, SDL_Event event);
static void On_Tick(TFrame *frame, TWindow *window);
static void On_Unload(TFrame *frame, TWindow *window);
static void Finish(TFrame *frame, TWindow *window);

static unsigned int sprite_speed = 1;

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
    SDL_Rect pos_sprite = {0, 0, 24, 24};
    TSprite *sp = New_TSprite("ICO", window, "images/sprite.png", pos_sprite);
    frame->Add_Sprite(frame, sp);
}

static void On_Load(TFrame* frame, TWindow *window)
{
    printf("Frame [%s]: On_Load method called | Window finished: %d\n", frame->frame_id, window->finished);
    TSprite *sprite = frame->Get_Sprite(frame, "ICO");
    sprite->pos.x = 0;
    sprite->pos.y = 0;
    sprite_speed = 1;

    // On définit la couleur de fond de la fenêtre.
    SDL_SetRenderDrawColor(window->renderer_window, 255, 0, 0, 255);
    SDL_RenderClear(window->renderer_window);
}

static void On_Event(TFrame* frame, TWindow *window, SDL_Event event)
{
    if (event.type == SDL_KEYDOWN) {
        TSprite *sprite = frame->Get_Sprite(frame, "ICO");

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
        TSprite *sprite = frame->Get_Sprite(frame, "ICO");

        if (event.key.keysym.sym == SDLK_KP_PLUS)
            sprite_speed += 5;
        if (event.key.keysym.sym == SDLK_KP_MINUS)
            sprite_speed -= 5;
        if (event.key.keysym.sym == SDLK_ESCAPE)
            window->Show_Frame(window, "FRAME_MENU");
        if (event.key.keysym.sym == SDLK_SPACE) {
            SDL_Rect pos_bomb = {sprite->pos.x, sprite->pos.y, 24, 24};
            TSprite *sp = New_TSprite("BOMB", window, "images/bomb.png", pos_bomb);

            frame->AddTop_Sprite(frame, sp);
        }
    }
}

static void On_Tick(TFrame* frame, TWindow *window)
{
    printf("Frame [%s]: On_Tick method called: %d | Window finished: %d\n", frame->frame_id, frame->initialized, window->finished);
    SDL_RenderClear(window->renderer_window);
    frame->Draw_Sprites(frame, window);
    SDL_RenderPresent(window->renderer_window);
}

static void On_Unload(TFrame* frame, TWindow *window)
{
    TSprite *bomb_sprite = frame->Remove_Sprite(frame, "BOMB");

    while (bomb_sprite) {
        bomb_sprite->Free(bomb_sprite);
        bomb_sprite = frame->Remove_Sprite(frame, "BOMB");
    }
    printf("Frame [%s]: On_Unload method called | Window finished: %d\n", frame->frame_id, window->finished);
}

static void Finish(TFrame* frame, TWindow *window)
{
    printf("Frame [%s]: Finish method called | Window finished: %d\n", frame->frame_id, window->finished);
}

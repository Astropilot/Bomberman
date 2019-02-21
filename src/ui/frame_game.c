/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the game frame.
*/

#include "ui/frame_game.h"
#include "core/player.h"
#include "main.h"

static void Init(TFrame *frame);
static void On_Load(TFrame *frame, int argc, va_list args);
static void On_Event(TFrame *frame, SDL_Event event);
static void On_Tick(TFrame *frame);
static void On_Unload(TFrame *frame);
static void Finish(TFrame *frame);

static TGameClient *gameclient;

TFrame* New_GameFrame(TGameClient *m_gameclient)
{
    TFrame *frm = New_TFrame("FRAME_GAME");
    frm->Init = Init;
    frm->On_Load = On_Load;
    frm->On_Event = On_Event;
    frm->On_Tick = On_Tick;
    frm->On_Unload = On_Unload;
    frm->Finish = Finish;
    gameclient = m_gameclient;
    return (frm);
}

static void Init(TFrame* frame)
{
    SDL_Rect pos_sprite2 = {0, 0, WIN_WIDTH, WIN_HEIGHT};
    TSprite *sp2 = New_TSprite(frame, "images/bomberman_game.png", pos_sprite2);

    frame->Add_Drawable(frame, (TDrawable*)sp2, "BG", 999);
}

static void On_Load(TFrame* frame, int argc, va_list args)
{
    if (IS_DEBUG)
        printf("Frame [%s]: On_Load method called | Argc: %d\n", frame->frame_id, argc);
    TClient *client = va_arg(args, TClient*);
    TGameServer *server = va_arg(args, TGameServer*);
    int player = va_arg(args, int);
    int nb_players = va_arg(args, int);
    int i;

    gameclient->client = client;
    if (server)
        gameclient->is_owner = 1;
    gameclient->gameserver = server;
    gameclient->player = player;

    for (i = 0; i < nb_players; i++) {
        char *player_id = malloc(sizeof(char) * 10);
        sprintf(player_id, "PLAYER_%d", (int)i);
        SDL_Rect pos = {0, 0, 64, 64};
        SDL_Rect size = {0, 0, 256, 256};
        TAnimatedSprite *asp = New_TAnimatedSprite(frame, "images/sprite_animated.png", size, pos, 100, -1);
        frame->Add_Drawable(frame, (TDrawable*)asp, player_id, 1);
        free(player_id);
    }

    gameclient->Ready(gameclient);

    SDL_RenderClear(frame->window->renderer_window);
}

static void On_Event(TFrame* frame, SDL_Event event)
{
    if (!frame) return;
    if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_ESCAPE)
            gameclient->Leave_Game(gameclient);
        if (event.key.keysym.sym == SDLK_SPACE) {
            gameclient->Place_Bomb(gameclient);
        }
    }
}

static void On_Tick(TFrame* frame)
{
    const Uint8 *keyboard = SDL_GetKeyboardState(NULL);

    if (keyboard[SDL_SCANCODE_LEFT]) {
        gameclient->Move(gameclient, OUEST);
    } else if (keyboard[SDL_SCANCODE_RIGHT]) {
        gameclient->Move(gameclient, EST);
    } else if (keyboard[SDL_SCANCODE_UP]) {
        gameclient->Move(gameclient, NORD);
    } else if (keyboard[SDL_SCANCODE_DOWN]) {
        gameclient->Move(gameclient, SUD);
    }

    SDL_RenderClear(frame->window->renderer_window);
    gameclient->Handle_Messages(gameclient);
    frame->Draw_Drawables(frame);
    SDL_RenderPresent(frame->window->renderer_window);
    if (frame->window->finished)
        gameclient->Leave_Game(gameclient);
}

static void On_Unload(TFrame* frame)
{
    if (IS_DEBUG)
        printf("Frame [%s]: On_Unload method called\n", frame->frame_id);

    TSprite *bomb_sprite = (TSprite*)frame->Remove_Drawable(frame, "BOMB");

    while (bomb_sprite) {
        bomb_sprite->Free(bomb_sprite);
        bomb_sprite = (TSprite*)frame->Remove_Drawable(frame, "BOMB");
    }
}

static void Finish(TFrame* frame)
{
    if (IS_DEBUG)
        printf("Frame [%s]: Finish method called\n", frame->frame_id);
    gameclient->Free(gameclient);
}

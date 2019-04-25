/*******************************************************************************
* PROJECT: Bomberman
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

#include <stdio.h>
#include <stdarg.h>

#include "main.h"
#include "glib.h"
#include "ui/scene_lobby.h"
#include "network/game/lobby.h"

static void On_Init(TScene *scene);
static void On_Load(TScene *scene, int argc, va_list args);
static void On_Event(TScene *scene, SDL_Event event);
static void On_Tick(TScene *scene);
static void On_Unload(TScene *scene);
static void On_Finish(TScene *scene);

static TButton *btn_start;
static TButton *btns_kick[MAX_PLAYERS];

static void On_Click_Start_Button(TButton *button, TScene *scene);
static void On_Click_Quit_Button(TButton *button, TScene *scene);
static void On_Click_Kick_Button(TButton *button, TScene *scene);

static TLobbyClient *lobbyclient;

TScene* New_LobbyScene(TLobbyClient *m_lobbyclient)
{
    TScene *frm = New_TScene("SCENE_LOBBY");
    if (frm) {
        frm->On_Init = On_Init;
        frm->On_Load = On_Load;
        frm->On_Event = On_Event;
        frm->On_Tick = On_Tick;
        frm->On_Unload = On_Unload;
        frm->On_Finish = On_Finish;
    }
    lobbyclient = m_lobbyclient;
    return (frm);
}

static void On_Init(TScene* scene)
{
    SDL_Rect pos_button_start = {15, WIN_HEIGHT - 64 - 15, 410, 64};
    btn_start = New_TButton(scene,
        RES_PATH "button_startgame_normal.png",
        RES_PATH "button_startgame_hover.png", pos_button_start
    );
    btn_start->On_Click = On_Click_Start_Button;

    SDL_Rect pos_button_quit = {WIN_WIDTH - 410 - 15, WIN_HEIGHT - 64 - 15, 410, 64};
    TButton *btn_quit = New_TButton(scene,
        RES_PATH "button_quitparty_normal.png",
        RES_PATH "button_quitparty_hover.png", pos_button_quit
    );
    btn_quit->On_Click = On_Click_Quit_Button;

    SDL_Rect pos_sprite_bg = {0, 0, 430, 242};
    SDL_Rect size_sprite_bg = {0, 0, 1280, 720};
    TAnimatedSprite *sp_bg = New_TAnimatedSprite(scene,
        RES_PATH "animated_background.png", pos_sprite_bg,
        size_sprite_bg, 52, -1
    );

    SDL_Rect pos_ui = {0, 0, 1280, 720};
    TSprite *sp_ui = New_TSprite(scene,
        RES_PATH "lobby_background.png", pos_ui
    );

    SDL_Rect size = {0, 0, 200, 200};
    SDL_Rect pos = {216, 589, 32, 32};
    TAnimatedSprites *sp_loader = New_TAnimatedSprites(scene,
        RES_PATH "loader/frame-%02d.png", 30, size, pos, 40, -1
    );

    int i;
    char *id_btn = malloc(sizeof(char) * 25);

    for (i = 0; i < MAX_PLAYERS; i++) {
        SDL_Rect pos_button_kick = {790, 216 + (i * 92) - 16, 32, 33};
        TButton *btn_kick = New_TButton(scene,
            RES_PATH "cross.png",
            RES_PATH "cross.png", pos_button_kick
        );

        btn_kick->is_visible = 0;
        btn_kick->On_Click = On_Click_Kick_Button;
        sprintf(id_btn, "BTN_KICK_%d", i);
        scene->Add_Drawable(scene, (TDrawable*)btn_kick,
            id_btn, 1, GLIB_FREE_ON_FINISH
        );
        btns_kick[i] = btn_kick;
    }
    free(id_btn);

    scene->Add_Drawable(scene, (TDrawable*)sp_bg,
        "BG", 999, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)sp_ui,
        "BG", 3, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)btn_start,
        "BTN_START", 1, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)btn_quit,
        "BTN_QUIT", 1, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)sp_loader,
        "LOADER", 1, GLIB_FREE_ON_FINISH
    );
}

static void On_Load(TScene* scene, int argc, va_list args)
{
    if (IS_DEBUG)
        printf("Scene [%s]: On_Load method called: %d\n", scene->scene_id, argc);

    lobby_args_t param = va_arg(args, lobby_args_t);

    SDL_Rect pos_label = {0, 0, 0, 0};
    SDL_Color color = {255, 255, 255, 255};
    TTF_Font *font = loadFont(FONT_PATH "fixedsys.ttf", 24);
    TText *txt_label = New_TText(scene, "Connexion en cours...", font, color, pos_label);
    txt_label->pos.x = (WIN_WIDTH / 2) - (txt_label->pos.w / 2);
    txt_label->pos.y = 585;

    scene->Add_Drawable(scene, (TDrawable*)txt_label,
        "LABEL_STATUS", 1, GLIB_FREE_ON_UNLOAD
    );

    TButton *btn_quit = (TButton*)scene->Get_Drawable(scene, "BTN_QUIT");

    btn_quit->state = BUTTON_NORMAL;

    if (scene->Is_BackgroundMusic_Playing(scene)) {
        scene->Pause_BackgroundMusic(scene, 1);
    }
    scene->Play_BackgroundMusic(scene, SOUND_PATH "lobby_bg.wav", -1);

    if (!param.server_ip) {
        lobbyclient->Start_Server(lobbyclient, param.port, param.game_rules);
        lobbyclient->Join_Lobby(lobbyclient, param.username, "127.0.0.1", param.port);
    } else {
        lobbyclient->Join_Lobby(lobbyclient, param.username, param.server_ip, param.port);
    }
}

static void On_Event(TScene* scene, SDL_Event event)
{
    TButton *btn_quit = (TButton*)scene->Get_Drawable(scene, "BTN_QUIT");
    char *id_btn = malloc(sizeof(char) * 25);
    int i;

    btn_quit->Event_Handler(btn_quit, scene, event);
    btn_start->Event_Handler(btn_start, scene, event);

    for (i = 0; i < MAX_PLAYERS; i++) {
        sprintf(id_btn, "BTN_KICK_%d", i);
        TButton *btn_kick = (TButton*)scene->Get_Drawable(scene, id_btn);

        btn_kick->Event_Handler(btn_kick, scene, event);
    }
    free(id_btn);
}

static void On_Click_Start_Button(TButton *button, TScene *scene)
{
    if (!button || !scene)
        printf("Button: Host Button pressed!\n");
    lobbyclient->Start_Game(lobbyclient);
}

static void On_Click_Quit_Button(TButton *button, TScene *scene)
{
    if (!button || !scene)
        printf("Button: Quit Button pressed!\n");
    lobbyclient->Leave_Lobby(lobbyclient, 1);
}

static void On_Click_Kick_Button(TButton *button, TScene *scene)
{
    int i;

    for (i = 0; i < MAX_PLAYERS; i++) {
        if (btns_kick[i] == button) {
            lobbyclient->Kick_Player(lobbyclient, i);
        }
    }
    (void)*scene;
}

static void On_Tick(TScene* scene)
{
    SDL_RenderClear(scene->window->renderer_window);
    lobbyclient->Handle_Messages(lobbyclient);
    if ((int)lobbyclient->nb_players >= lobbyclient->rules.min_players && lobbyclient->is_owner)
        btn_start->is_visible = 1;
    else
        btn_start->is_visible = 0;
    scene->Draw_Drawables(scene);
    SDL_RenderPresent(scene->window->renderer_window);
    if (scene->window->finished)
        lobbyclient->Leave_Lobby(lobbyclient, 1);
}

static void On_Unload(TScene* scene)
{
    if (IS_DEBUG)
        printf("Scene [%s]: On_Unload method called\n", scene->scene_id);
    scene->Pause_BackgroundMusic(scene, 1);
}

static void On_Finish(TScene* scene)
{
    if (IS_DEBUG)
        printf("Scene [%s]: Finish method called\n", scene->scene_id);
    lobbyclient->Free(lobbyclient);
}

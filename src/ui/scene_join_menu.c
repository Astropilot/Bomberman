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

#include "glib.h"
#include "main.h"
#include "ui/scene_host_menu.h"

static void On_Init(TScene *scene);
static void On_Load(TScene *scene, int argc, va_list args);
static void On_Event(TScene *scene, SDL_Event event);
static void On_Tick(TScene *scene);
static void On_Unload(TScene *scene);
static void On_Finish(TScene *scene);

static void On_Click_Play_Button(TButton *button, TScene *scene);

TScene* New_JoinMenuScene(void)
{
    TScene *frm = New_TScene("SCENE_JOIN_MENU");
    if (frm) {
        frm->On_Init = On_Init;
        frm->On_Load = On_Load;
        frm->On_Event = On_Event;
        frm->On_Tick = On_Tick;
        frm->On_Unload = On_Unload;
        frm->On_Finish = On_Finish;
    }
    return (frm);
}

static void On_Init(TScene* scene)
{
    TTF_Font *font = NULL;
    SDL_Color color = {255, 255, 255, 255};
    SDL_Rect pos_sprite_bg = {0, 0, 430, 242};
    SDL_Rect size_sprite_bg = {0, 0, 1280, 720};
    TAnimatedSprite *sp_bg = New_TAnimatedSprite(scene,
        RES_PATH "animated_background.png", pos_sprite_bg,
        size_sprite_bg, 52, -1
    );

    SDL_Rect pos_title = {(WIN_WIDTH / 2) - (644 / 2), 100, 644, 104};
    TSprite *sp_title = New_TSprite(scene,
        RES_PATH "bomberman_logo_title.png", pos_title
    );

    SDL_Rect pos = {(WIN_WIDTH / 2) - (400 / 2), 250, 400, 92};
    TSprite *sprite_input_username = New_TSprite(scene, RES_PATH "input.png", pos);
    font = loadFont(FONT_PATH "fixedsys.ttf", 24);
    TInput *input_username = New_TInput(scene, sprite_input_username,
        color, 15, "Username", font
    );

    SDL_Rect pos2 = {(WIN_WIDTH / 2) - (400 / 2), (pos.y + pos.h) + 15, 400, 92};
    TSprite *sprite_input_serverip = New_TSprite(scene, RES_PATH "input.png", pos2);
    font = loadFont(FONT_PATH "fixedsys.ttf", 24);
    TInput *input_serverip = New_TInput(scene, sprite_input_serverip,
        color, 15, "Server IP", font
    );

    SDL_Rect pos3 = {(WIN_WIDTH / 2) - (400 / 2), (pos2.y + pos2.h) + 15, 400, 92};
    TSprite *sprite_input_serverport = New_TSprite(scene, RES_PATH "input.png", pos3);
    font = loadFont(FONT_PATH "fixedsys.ttf", 24);
    TInput *input_serverport = New_TInput(scene, sprite_input_serverport,
        color, 5, "Server port", font
    );

    SDL_Rect pos_button_play = {(WIN_WIDTH / 2) - (410 / 2), (pos3.y + pos3.h) + 15, 410, 64};
    TButton *btn_play = New_TButton(scene,
        RES_PATH "button_join_normal.png",
        RES_PATH "button_join_hover.png", pos_button_play
    );
    btn_play->On_Click = On_Click_Play_Button;

    scene->Add_Drawable(scene, (TDrawable*)sp_bg,
        "BG", 999, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)sp_title,
        "TITLE", 998, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)input_username,
        "INPUT_USER", 1, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)input_serverip,
        "INPUT_IP", 1, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)input_serverport,
        "INPUT_PORT", 1, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)btn_play,
        "BTN_PLAY", 1, GLIB_FREE_ON_FINISH
    );
}

static void On_Load(TScene* scene, int argc, va_list args)
{
    if (IS_DEBUG)
        printf("Scene [%s]: On_Load method called | Args: [%d] %p\n", scene->scene_id, argc, &args);
    TInput *input_username = (TInput*)scene->Get_Drawable(scene, "INPUT_USER");
    TInput *input_serverip = (TInput*)scene->Get_Drawable(scene, "INPUT_IP");
    TInput *input_serverport = (TInput*)scene->Get_Drawable(scene, "INPUT_PORT");
    TButton *btn_play = (TButton*)scene->Get_Drawable(scene, "BTN_PLAY");

    SDL_StartTextInput();

    btn_play->state = BUTTON_NORMAL;
    strcpy(input_username->text, "");
    strcpy(input_serverip->text, "");
    strcpy(input_serverport->text, "");

    if (scene->Is_BackgroundMusic_Paused(scene) && scene->Is_BackgroundMusic_Playing(scene)) {
        scene->Resume_BackgroundMusic(scene);
    } else {
        scene->Play_BackgroundMusic(scene, SOUND_PATH "theme_bg.wav", -1);
    }
}

static void On_Event(TScene* scene, SDL_Event event)
{
    TInput *input_username = (TInput*)scene->Get_Drawable(scene, "INPUT_USER");
    TInput *input_serverip = (TInput*)scene->Get_Drawable(scene, "INPUT_IP");
    TInput *input_serverport = (TInput*)scene->Get_Drawable(scene, "INPUT_PORT");
    TButton *btn_play = (TButton*)scene->Get_Drawable(scene, "BTN_PLAY");

    btn_play->Event_Handler(btn_play, scene, event);
    input_username->Event_Handler(input_username, event);
    input_serverip->Event_Handler(input_serverip, event);
    input_serverport->Event_Handler(input_serverport, event);
    if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_ESCAPE)
            scene->window->Show_Scene(scene->window, "SCENE_MAIN_MENU", 0);
    }
}

static void On_Click_Play_Button(TButton *button, TScene *scene)
{
    if (IS_DEBUG)
        printf("Button [%p]: Play Button pressed!\n", button);
    TInput *input_username = (TInput*)scene->Get_Drawable(scene, "INPUT_USER");
    TInput *input_ip = (TInput*)scene->Get_Drawable(scene, "INPUT_IP");
    TInput *input_port = (TInput*)scene->Get_Drawable(scene, "INPUT_PORT");

    if (strlen(input_username->text) > 0) {
        int port = atoi(input_port->text);
        lobby_args_t params = {input_username->text, input_ip->text, port};
        scene->window->Show_Scene(scene->window, "SCENE_LOBBY", 1, params);
    }
}

static void On_Tick(TScene* scene)
{
    SDL_RenderClear(scene->window->renderer_window);
    scene->Draw_Drawables(scene);
    SDL_RenderPresent(scene->window->renderer_window);
}

static void On_Unload(TScene* scene)
{
    if (IS_DEBUG)
        printf("Scene [%s]: On_Unload method called\n", scene->scene_id);
    SDL_StopTextInput();
    scene->Pause_BackgroundMusic(scene, 0);
}

static void On_Finish(TScene* scene)
{
    if (IS_DEBUG)
        printf("Scene [%s]: Finish method called\n", scene->scene_id);
}

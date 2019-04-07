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
#include "ui/scene_main_menu.h"

static void Init(TScene* scene);
static void On_Load(TScene* scene, int argc, va_list args);
static void On_Event(TScene* scene, SDL_Event event);
static void On_Tick(TScene* scene);
static void On_Unload(TScene* scene);
static void Finish(TScene* scene);

static void On_Click_Host_Button(TButton *button, TScene *scene);
static void On_Click_Join_Button(TButton *button, TScene *scene);
static void On_Click_Quit_Button(TButton *button, TScene *scene);

TScene* New_MainMenuScene(void)
{
    TScene *frm = New_TScene("SCENE_MAIN_MENU");
    if (frm) {
        frm->Init = Init;
        frm->On_Load = On_Load;
        frm->On_Event = On_Event;
        frm->On_Tick = On_Tick;
        frm->On_Unload = On_Unload;
        frm->Finish = Finish;
    }
    return (frm);
}

static void Init(TScene* scene)
{
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

    SDL_Rect pos_button_host = {(WIN_WIDTH / 2) - (410 / 2), 250, 410, 64};
    TButton *btn_host = New_TButton(scene,
        RES_PATH "button_host_normal.png",
        RES_PATH "button_host_hover.png", pos_button_host
    );
    btn_host->On_Click = On_Click_Host_Button;

    SDL_Rect pos_button_join = {(WIN_WIDTH / 2) - (410 / 2), (pos_button_host.y + pos_button_host.h)+15, 410, 64};
    TButton *btn_join = New_TButton(scene,
        RES_PATH "button_connect_normal.png",
        RES_PATH "button_connect_hover.png", pos_button_join
    );
    btn_join->On_Click = On_Click_Join_Button;

    SDL_Rect pos_button_quit = {(WIN_WIDTH / 2) - (410 / 2), (pos_button_join.y + pos_button_join.h)+15, 410, 64};
    TButton *btn_quit = New_TButton(scene,
        RES_PATH "button_quit_normal.png",
        RES_PATH "button_quit_hover.png", pos_button_quit
    );
    btn_quit->On_Click = On_Click_Quit_Button;

    SDL_Rect pos_txt = { 0, 0, 0, 0 };
    SDL_Color color = { 255, 255, 255, 255 };
    TTF_Font *font = loadFont(FONT_PATH "fixedsys.ttf", 18);
    TText *txt_version = New_TText(scene, "Version: " GAME_VERSION,
        font, color, pos_txt
    );
    txt_version->pos.y = WIN_HEIGHT - txt_version->pos.h;

    scene->Add_Drawable(scene, (TDrawable*)sp_bg,
        "BG", 999, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)sp_title,
        "TITLE", 998, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)txt_version,
        "TXT_VERSION", 2, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)btn_host,
        "BTN_HOST", 1, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)btn_join,
        "BTN_JOIN", 1, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)btn_quit,
        "BTN_QUIT", 1, GLIB_FREE_ON_FINISH
    );
}

static void On_Load(TScene* scene, int argc, va_list args)
{
    if (IS_DEBUG)
        printf("Scene [%s]: On_Load method called | Args: [%d] %p\n", scene->scene_id, argc, &args);

    TButton *btn_host = (TButton*)scene->Get_Drawable(scene, "BTN_HOST");
    TButton *btn_join = (TButton*)scene->Get_Drawable(scene, "BTN_JOIN");
    TButton *btn_quit = (TButton*)scene->Get_Drawable(scene, "BTN_QUIT");

    btn_host->state = BUTTON_NORMAL;
    btn_join->state = BUTTON_NORMAL;
    btn_quit->state = BUTTON_NORMAL;
}

static void On_Event(TScene* scene, SDL_Event event)
{
    TButton *btn_host = (TButton*)scene->Get_Drawable(scene, "BTN_HOST");
    TButton *btn_join = (TButton*)scene->Get_Drawable(scene, "BTN_JOIN");
    TButton *btn_quit = (TButton*)scene->Get_Drawable(scene, "BTN_QUIT");

    btn_host->Event_Handler(btn_host, scene, event);
    btn_join->Event_Handler(btn_join, scene, event);
    btn_quit->Event_Handler(btn_quit, scene, event);
}

static void On_Click_Host_Button(TButton *button, TScene *scene)
{
    if (IS_DEBUG)
        printf("Button [%p]: Host Button pressed!\n", button);
    scene->window->Show_Scene(scene->window, "SCENE_HOST_MENU", 0);
}

static void On_Click_Join_Button(TButton *button, TScene *scene)
{
    if (IS_DEBUG)
        printf("Button [%p]: Join Button pressed!\n", button);
    scene->window->Show_Scene(scene->window, "SCENE_JOIN_MENU", 0);
}

static void On_Click_Quit_Button(TButton *button, TScene *scene)
{
    if (IS_DEBUG)
        printf("Button [%p]: Quit Button pressed!\n", button);
    scene->window->finished = 1;
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
}

static void Finish(TScene* scene)
{
    if (IS_DEBUG)
        printf("Scene [%s]: Finish method called\n", scene->scene_id);
}

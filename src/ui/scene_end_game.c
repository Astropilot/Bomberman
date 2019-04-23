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
#include "core/player.h"
#include "network/packets/packet_ack_endgame.h"
#include "ui/scene_end_game.h"

static void Init(TScene* scene);
static void On_Load(TScene* scene, int argc, va_list args);
static void On_Event(TScene* scene, SDL_Event event);
static void On_Tick(TScene* scene);
static void On_Unload(TScene* scene);
static void Finish(TScene* scene);

static void On_Click_Menu_Button(TButton *button, TScene *scene);

TScene* New_EndGameScene(void)
{
    TScene *frm = New_TScene("SCENE_END_GAME");
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
    SDL_Rect pos_button = {(WIN_WIDTH / 2) - (410 / 2), WIN_HEIGHT - 64 - 15, 410, 64};
    TButton *btn_menu = New_TButton(scene,
        RES_PATH "button_backmenu_normal.png",
        RES_PATH "button_backmenu_hover.png", pos_button
    );
    btn_menu->On_Click = On_Click_Menu_Button;

    scene->Add_Drawable(scene, (TDrawable*)btn_menu,
        "BTN_MENU", 1, GLIB_FREE_ON_FINISH
    );
}

static void On_Load(TScene* scene, int argc, va_list args)
{
    if (IS_DEBUG)
        printf("Scene [%s]: On_Load method called: %d\n", scene->scene_id, argc);

    SDL_Rect pos_label = {0, 0, 0, 0};
    SDL_Color color = {255, 255, 255, 255};
    TTF_Font *font = loadFont(FONT_PATH "fixedsys.ttf", 24);
    game_result_t game_res = va_arg(args, game_result_t);
    player_t *winner = va_arg(args, player_t*);
    TButton *btn_menu = (TButton*)scene->Get_Drawable(scene, "BTN_MENU");
    TText *txt_label;
    char *string_label = malloc(sizeof(char) * 255);

    if (game_res == WINNER) {
        sprintf(string_label, "VAINQUEUR: %s !", winner->username);
    } else {
        sprintf(string_label, "EGALITE ! AUCUN VAINQUEUR !");
    }

    txt_label = New_TText(scene, string_label, font, color, pos_label);
    btn_menu->state = BUTTON_NORMAL;
    txt_label->pos.x = (WIN_WIDTH / 2) - (txt_label->pos.w / 2);
    txt_label->pos.y = (WIN_HEIGHT / 2) - (txt_label->pos.h / 2);
    free(string_label);
    if (winner) {
        free(winner->username);
        free(winner);
    }
    scene->Add_Drawable(scene, (TDrawable*)txt_label,
        "LABEL_STATUS", 1, GLIB_FREE_ON_UNLOAD
    );
}

static void On_Event(TScene* scene, SDL_Event event)
{
    TButton *btn_menu = (TButton*)scene->Get_Drawable(scene, "BTN_MENU");

    btn_menu->Event_Handler(btn_menu, scene, event);
}

static void On_Click_Menu_Button(TButton *button, TScene *scene)
{
    if (IS_DEBUG)
        printf("Button [%p]: Play Button pressed!\n", button);
    scene->window->Show_Scene(scene->window, "SCENE_MAIN_MENU", 0);
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
    scene->Pause_BackgroundMusic(scene, 1);
}

static void Finish(TScene* scene)
{
    if (IS_DEBUG)
        printf("Scene [%s]: Finish method called\n", scene->scene_id);
}

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
#include "ui/frame_end_game.h"

static void Init(TFrame* frame);
static void On_Load(TFrame* frame, int argc, va_list args);
static void On_Event(TFrame* frame, SDL_Event event);
static void On_Tick(TFrame* frame);
static void On_Unload(TFrame* frame);
static void Finish(TFrame* frame);

static void On_Click_Menu_Button(TButton *button, TFrame *frame);

TFrame* New_EndGameFrame(void)
{
    TFrame *frm = New_TFrame("FRAME_END_GAME");
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

static void Init(TFrame* frame)
{
    SDL_Rect pos_button = {(WIN_WIDTH / 2) - (410 / 2), WIN_HEIGHT - 64 - 15, 410, 64};
    TButton *btn_menu = New_TButton(frame, RES_PATH "button_backmenu_normal.png", RES_PATH "button_backmenu_hover.png", pos_button);
    btn_menu->On_Click = On_Click_Menu_Button;

    frame->Add_Drawable(frame, (TDrawable*)btn_menu, "BTN_MENU", 1);
}

static void On_Load(TFrame* frame, int argc, va_list args)
{
    if (IS_DEBUG)
        printf("Frame [%s]: On_Load method called: %d\n", frame->frame_id, argc);

    SDL_Rect pos_label = {0, 0, 0, 0};
    SDL_Color color = {255, 255, 255, 255};
    TTF_Font *font = loadFont(FONT_PATH "fixedsys.ttf", 24);
    game_result_t game_res = va_arg(args, game_result_t);
    player_t *winner = va_arg(args, player_t*);
    TButton *btn_menu = (TButton*)frame->Get_Drawable(frame, "BTN_MENU");
    TText *txt_label;
    char *string_label = malloc(sizeof(char) * 255);

    if (game_res == WINNER) {
        sprintf(string_label, "VAINQUEUR: %s !", winner->username);
    } else {
        sprintf(string_label, "EGALITE ! AUCUN VAINQUEUR !");
    }

    txt_label = New_TText(frame, string_label, font, color, pos_label);
    btn_menu->state = BUTTON_NORMAL;
    txt_label->pos.x = (WIN_WIDTH / 2) - (txt_label->pos.w / 2);
    txt_label->pos.y = (WIN_HEIGHT / 2) - (txt_label->pos.h / 2);
    free(string_label);
    if (winner) {
        free(winner->username);
        free(winner);
    }
    frame->Add_Drawable(frame, (TDrawable*)txt_label, "LABEL_STATUS", 1);
}

static void On_Event(TFrame* frame, SDL_Event event)
{
    TButton *btn_menu = (TButton*)frame->Get_Drawable(frame, "BTN_MENU");

    btn_menu->Event_Handler(btn_menu, frame, event);
}

static void On_Click_Menu_Button(TButton *button, TFrame *frame)
{
    if (IS_DEBUG)
        printf("Button [%p]: Play Button pressed!\n", button);
    frame->window->Show_Frame(frame->window, "FRAME_MAIN_MENU", 0);
}

static void On_Tick(TFrame* frame)
{
    SDL_RenderClear(frame->window->renderer_window);
    frame->Draw_Drawables(frame);
    SDL_RenderPresent(frame->window->renderer_window);
}

static void On_Unload(TFrame* frame)
{
    frame->Free_Drawable(frame, "LABEL_STATUS");
}

static void Finish(TFrame* frame)
{
    if (IS_DEBUG)
        printf("Frame [%s]: Finish method called\n", frame->frame_id);
}

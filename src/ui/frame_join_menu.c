/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the join menu frame.
*/

#include <stdio.h>
#include <stdarg.h>

#include "glib.h"
#include "main.h"
#include "ui/frame_host_menu.h"

static void Init(TFrame* frame);
static void On_Load(TFrame* frame, int argc, va_list args);
static void On_Event(TFrame* frame, SDL_Event event);
static void On_Tick(TFrame* frame);
static void On_Unload(TFrame* frame);
static void Finish(TFrame* frame);

static void On_Click_Play_Button(TButton *button, TFrame *frame);

TFrame* New_JoinMenuFrame(void)
{
    TFrame *frm = New_TFrame("FRAME_JOIN_MENU");
    frm->Init = Init;
    frm->On_Load = On_Load;
    frm->On_Event = On_Event;
    frm->On_Tick = On_Tick;
    frm->On_Unload = On_Unload;
    frm->Finish = Finish;
    return (frm);
}

static void Init(TFrame* frame)
{
    SDL_Color color = {255, 255, 255, 255};
    SDL_Rect pos_sprite_bg = {0, 0, 430, 242};
    SDL_Rect size_sprite_bg = {0, 0, 1280, 720};
    TAnimatedSprite *sp_bg = New_TAnimatedSprite(frame, RES_PATH "animated_background.png", pos_sprite_bg, size_sprite_bg, 52, -1);

    SDL_Rect pos_title = {(WIN_WIDTH / 2) - (644 / 2), 100, 644, 104};
    TSprite *sp_title = New_TSprite(frame, RES_PATH "bomberman_logo_title.png", pos_title);

    SDL_Rect pos = {(WIN_WIDTH / 2) - (400 / 2), 250, 400, 92};
    TInput *input_username = New_TInput(frame, RES_PATH "input.png", pos, color, 15, "Username");

    SDL_Rect pos2 = {(WIN_WIDTH / 2) - (400 / 2), (pos.y + pos.h) + 15, 400, 92};
    TInput *input_serverip = New_TInput(frame, RES_PATH "input.png", pos2, color, 15, "Server IP");

    SDL_Rect pos3 = {(WIN_WIDTH / 2) - (400 / 2), (pos2.y + pos2.h) + 15, 400, 92};
    TInput *input_serverport = New_TInput(frame, RES_PATH "input.png", pos3, color, 5, "Server port");

    SDL_Rect pos_button_play = {(WIN_WIDTH / 2) - (410 / 2), (pos3.y + pos3.h) + 15, 410, 64};
    TButton *btn_play = New_TButton(frame, RES_PATH "button_join_normal.png", RES_PATH "button_join_hover.png", pos_button_play);
    btn_play->On_Click = On_Click_Play_Button;

    frame->Add_Drawable(frame, (TDrawable*)sp_bg, "BG", 999);
    frame->Add_Drawable(frame, (TDrawable*)sp_title, "TITLE", 998);
    frame->Add_Drawable(frame, (TDrawable*)input_username, "INPUT_USER", 1);
    frame->Add_Drawable(frame, (TDrawable*)input_serverip, "INPUT_IP", 1);
    frame->Add_Drawable(frame, (TDrawable*)input_serverport, "INPUT_PORT", 1);
    frame->Add_Drawable(frame, (TDrawable*)btn_play, "BTN_PLAY", 1);
}

static void On_Load(TFrame* frame, int argc, va_list args)
{
    if (IS_DEBUG)
        printf("Frame [%s]: On_Load method called | Args: [%d] %p\n", frame->frame_id, argc, &args);
    TInput *input_username = (TInput*)frame->Get_Drawable(frame, "INPUT_USER");
    TInput *input_serverip = (TInput*)frame->Get_Drawable(frame, "INPUT_IP");
    TInput *input_serverport = (TInput*)frame->Get_Drawable(frame, "INPUT_PORT");
    TButton *btn_play = (TButton*)frame->Get_Drawable(frame, "BTN_PLAY");

    SDL_StartTextInput();

    btn_play->state = BUTTON_NORMAL;
    strcpy(input_username->text, "");
    strcpy(input_serverip->text, "");
    strcpy(input_serverport->text, "");
}

static void On_Event(TFrame* frame, SDL_Event event)
{
    TInput *input_username = (TInput*)frame->Get_Drawable(frame, "INPUT_USER");
    TInput *input_serverip = (TInput*)frame->Get_Drawable(frame, "INPUT_IP");
    TInput *input_serverport = (TInput*)frame->Get_Drawable(frame, "INPUT_PORT");
    TButton *btn_play = (TButton*)frame->Get_Drawable(frame, "BTN_PLAY");

    btn_play->Event_Handler(btn_play, frame, event);
    input_username->Event_Handler(input_username, event);
    input_serverip->Event_Handler(input_serverip, event);
    input_serverport->Event_Handler(input_serverport, event);
    if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_ESCAPE)
            frame->window->Show_Frame(frame->window, "FRAME_MAIN_MENU", 0);
    }
}

static void On_Click_Play_Button(TButton *button, TFrame *frame)
{
    if (IS_DEBUG)
        printf("Button [%p]: Play Button pressed!\n", button);
    TInput *input_username = (TInput*)frame->Get_Drawable(frame, "INPUT_USER");
    TInput *input_ip = (TInput*)frame->Get_Drawable(frame, "INPUT_IP");
    TInput *input_port = (TInput*)frame->Get_Drawable(frame, "INPUT_PORT");

    if (strlen(input_username->text) > 0) {
        int port = atoi(input_port->text);
        lobby_args_t params = {input_username->text, input_ip->text, port};
        frame->window->Show_Frame(frame->window, "FRAME_LOBBY", 1, params);
    }
}

static void On_Tick(TFrame* frame)
{
    SDL_RenderClear(frame->window->renderer_window);
    frame->Draw_Drawables(frame);
    SDL_RenderPresent(frame->window->renderer_window);
}

static void On_Unload(TFrame* frame)
{
    if (IS_DEBUG)
        printf("Frame [%s]: On_Unload method called\n", frame->frame_id);
    SDL_StopTextInput();
}

static void Finish(TFrame* frame)
{
    if (IS_DEBUG)
        printf("Frame [%s]: Finish method called\n", frame->frame_id);
}

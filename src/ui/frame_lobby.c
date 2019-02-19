/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the lobby frame.
*/

#include "ui/frame_lobby.h"
#include "main.h"

static void Init(TFrame* frame);
static void On_Load(TFrame* frame, int argc, va_list args);
static void On_Event(TFrame* frame, SDL_Event event);
static void On_Tick(TFrame* frame);
static void On_Unload(TFrame* frame);
static void Finish(TFrame* frame);

static TButton *btn_start;

static void On_Click_Start_Button(TButton *button, TFrame *frame);
static void On_Click_Quit_Button(TButton *button, TFrame *frame);

static TLobbyClient *lobbyclient;

TFrame* New_LobbyFrame(TLobbyClient *m_lobbyclient)
{
    TFrame *frm = New_TFrame("FRAME_LOBBY");
    frm->Init = Init;
    frm->On_Load = On_Load;
    frm->On_Event = On_Event;
    frm->On_Tick = On_Tick;
    frm->On_Unload = On_Unload;
    frm->Finish = Finish;
    lobbyclient = m_lobbyclient;
    return (frm);
}

static void Init(TFrame* frame)
{
    SDL_Rect pos_button_start = {(WIN_WIDTH / 2) - (410 / 2), 400, 410, 64};
    btn_start = New_TButton(frame, "images/button_startgame_normal.png", "images/button_startgame_hover.png", pos_button_start);
    btn_start->On_Click = On_Click_Start_Button;

    SDL_Rect pos_button_quit = {(WIN_WIDTH / 2) - (410 / 2), (pos_button_start.y + pos_button_start.h) + 15, 410, 64};
    TButton *btn_quit = New_TButton(frame, "images/button_quit_normal.png", "images/button_quit_hover.png", pos_button_quit);
    btn_quit->On_Click = On_Click_Quit_Button;

    frame->Add_Drawable(frame, (TDrawable*)btn_quit, "BTN_QUIT", 1);
}

static void On_Load(TFrame* frame, int argc, va_list args)
{
    if (IS_DEBUG)
        printf("Frame [%s]: On_Load method called: %d\n", frame->frame_id, argc);

    lobby_args_t param = va_arg(args, lobby_args_t);

    if (!param.server_ip) {
        lobbyclient->Start_Server(lobbyclient, param.port, 2);
        lobbyclient->Join_Lobby(lobbyclient, param.username, "127.0.0.1", param.port);
    } else {
        lobbyclient->Join_Lobby(lobbyclient, param.username, param.server_ip, param.port);
    }

    SDL_Rect pos_label = {0, 0, 0, 0};
    SDL_Color color = {255, 255, 255, 255};
    TText *txt_label = New_TText(frame, "Connexion en cours...", TTF_OpenFont("fonts/fixedsys.ttf", 24), color, pos_label);
    txt_label->pos.x = (WIN_WIDTH / 2) - (txt_label->pos.w / 2);
    txt_label->pos.y = (WIN_HEIGHT / 2) - (txt_label->pos.h / 2);

    frame->Add_Drawable(frame, (TDrawable*)txt_label, "LABEL_STATUS", 1);

    TButton *btn_quit = (TButton*)frame->Get_Drawable(frame, "BTN_QUIT");

    btn_quit->state = BUTTON_NORMAL;
}

static void On_Event(TFrame* frame, SDL_Event event)
{
    TButton *btn_quit = (TButton*)frame->Get_Drawable(frame, "BTN_QUIT");

    btn_quit->Event_Handler(btn_quit, frame, event);
    if (lobbyclient->nb_players >= 2 && lobbyclient->is_owner)
        btn_start->Event_Handler(btn_start, frame, event);
}

static void On_Click_Start_Button(TButton *button, TFrame *frame)
{
    if (!button || !frame)
        printf("Button: Host Button pressed!\n");
    lobbyclient->Start_Game(lobbyclient);
}

static void On_Click_Quit_Button(TButton *button, TFrame *frame)
{
    if (!button || !frame)
        printf("Button: Join Button pressed!\n");
    lobbyclient->Leave_Lobby(lobbyclient);
}

static void On_Tick(TFrame* frame)
{
    SDL_RenderClear(frame->window->renderer_window);
    lobbyclient->Handle_Messages(lobbyclient);
    if (lobbyclient->nb_players >= 2 && lobbyclient->is_owner) {
        frame->Add_Drawable(frame, (TDrawable*)btn_start, "BTN_START", 1);
    } else {
        frame->Remove_Drawable(frame, "BTN_START");
    }
    frame->Draw_Drawables(frame);
    SDL_RenderPresent(frame->window->renderer_window);
}

static void On_Unload(TFrame* frame)
{
    if (IS_DEBUG)
        printf("Frame [%s]: On_Unload method called\n", frame->frame_id);
    TText *txt_label = (TText*)frame->Remove_Drawable(frame, "LABEL_STATUS");
    if (txt_label)
        txt_label->Free(txt_label);
}

static void Finish(TFrame* frame)
{
    if (IS_DEBUG)
        printf("Frame [%s]: Finish method called\n", frame->frame_id);
    //lobbyclient->Free(lobbyclient);
}

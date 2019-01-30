/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the join menu frame.
*/

#include "frame_host_menu.h"
#include "main.h"

static void Init(TFrame* frame, TWindow *window);
static void On_Load(TFrame* frame, TWindow *window, va_list args);
static void On_Event(TFrame* frame, TWindow *window, SDL_Event event);
static void On_Tick(TFrame* frame, TWindow *window);
static void On_Unload(TFrame* frame, TWindow *window);
static void Finish(TFrame* frame, TWindow *window);

static char *ptr_username;

static void On_Click_Play_Button(TButton *button, TWindow *window);

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

static void Init(TFrame* frame, TWindow *window)
{
    SDL_Color color = {255, 255, 255, 255};
    SDL_Rect pos_sprite_bg = {0, 0, 430, 242};
    SDL_Rect size_sprite_bg = {0, 0, 1280, 720};
    TAnimatedSprite *sp_bg = New_TAnimatedSprite(window, "images/animated_background.png", pos_sprite_bg, size_sprite_bg, 52);

    SDL_Rect pos_title = {(WIN_WIDTH / 2) - (644 / 2), 100, 644, 104};
    TSprite *sp_title = New_TSprite(window, "images/bomberman_logo_title.png", pos_title);

    SDL_Rect pos = {(WIN_WIDTH / 2) - (400 / 2), 250, 400, 92};
    TInput *input_username = New_TInput("images/input.png", pos, window, color, 15, "Username");
    ptr_username = (input_username->text);

    SDL_Rect pos2 = {(WIN_WIDTH / 2) - (400 / 2), (pos.y + pos.h) + 15, 400, 92};
    TInput *input_serverip = New_TInput("images/input.png", pos2, window, color, 15, "Server IP");

    SDL_Rect pos3 = {(WIN_WIDTH / 2) - (400 / 2), (pos2.y + pos2.h) + 15, 400, 92};
    TInput *input_serverport = New_TInput("images/input.png", pos3, window, color, 5, "Server port");

    SDL_Rect pos_button_play = {(WIN_WIDTH / 2) - (410 / 2), (pos3.y + pos3.h) + 15, 410, 64};
    TButton *btn_play = New_TButton("images/button_join_normal.png", "images/button_join_hover.png", pos_button_play, window);
    btn_play->On_Click = On_Click_Play_Button;

    frame->Add_Drawable(frame, (void*)sp_bg, ANIMATED_SPRITE, "BG", 999);
    frame->Add_Drawable(frame, (void*)sp_title, SPRITE, "TITLE", 998);
    frame->Add_Drawable(frame, (void*)input_username, INPUT, "INPUT_USER", 1);
    frame->Add_Drawable(frame, (void*)input_serverip, INPUT, "INPUT_IP", 1);
    frame->Add_Drawable(frame, (void*)input_serverport, INPUT, "INPUT_PORT", 1);
    frame->Add_Drawable(frame, (void*)btn_play, BUTTON, "BTN_PLAY", 1);
}

static void On_Load(TFrame* frame, TWindow *window, va_list args)
{
    if (IS_DEBUG)
        printf("Frame [%s]: On_Load method called | Window finished: %d, %p\n", frame->frame_id, window->finished, &args);
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

static void On_Event(TFrame* frame, TWindow *window, SDL_Event event)
{
    TInput *input_username = (TInput*)frame->Get_Drawable(frame, "INPUT_USER");
    TInput *input_serverip = (TInput*)frame->Get_Drawable(frame, "INPUT_IP");
    TInput *input_serverport = (TInput*)frame->Get_Drawable(frame, "INPUT_PORT");
    TButton *btn_play = (TButton*)frame->Get_Drawable(frame, "BTN_PLAY");

    btn_play->Event_Handler(btn_play, window, event);
    input_username->Event_Handler(input_username, window, event);
    input_serverip->Event_Handler(input_serverip, window, event);
    input_serverport->Event_Handler(input_serverport, window, event);
}

static void On_Click_Play_Button(TButton *button, TWindow *window)
{
    if (IS_DEBUG)
        printf("Button [%p]: Play Button pressed!\n", button);
    window->Show_Frame(window, "FRAME_GAME", 1, ptr_username);
}

static void On_Tick(TFrame* frame, TWindow *window)
{
    SDL_RenderClear(window->renderer_window);
    frame->Draw_Drawables(frame, window);
    SDL_RenderPresent(window->renderer_window);
}

static void On_Unload(TFrame* frame, TWindow *window)
{
    if (IS_DEBUG)
        printf("Frame [%s]: On_Unload method called | Window finished: %d\n", frame->frame_id, window->finished);
    SDL_StopTextInput();
}

static void Finish(TFrame* frame, TWindow *window)
{
    if (IS_DEBUG)
        printf("Frame [%s]: Finish method called | Window finished: %d\n", frame->frame_id, window->finished);
}

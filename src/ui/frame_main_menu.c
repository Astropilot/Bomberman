/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the main menu frame.
*/

#include "ui/frame_main_menu.h"
#include "main.h"

static void Init(TFrame* frame);
static void On_Load(TFrame* frame, int argc, va_list args);
static void On_Event(TFrame* frame, SDL_Event event);
static void On_Tick(TFrame* frame);
static void On_Unload(TFrame* frame);
static void Finish(TFrame* frame);

static void On_Click_Host_Button(TButton *button, TFrame *frame);
static void On_Click_Join_Button(TButton *button, TFrame *frame);
static void On_Click_Quit_Button(TButton *button, TFrame *frame);

TFrame* New_MainMenuFrame(void)
{
    TFrame *frm = New_TFrame("FRAME_MAIN_MENU");
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
    SDL_Rect size_sprite_bg = {0, 0, 960, 540};
    SDL_Rect pos_sprite_bg = {0, 0, 1280, 720};
    TAnimatedSprites *sp_bg = New_TAnimatedSprites(frame, "images/mainmenu/fire%02d.png", 47, size_sprite_bg, pos_sprite_bg , 20, -1);

    SDL_Rect pos_title = {(WIN_WIDTH / 2) - (644 / 2), 100, 644, 104};
    TSprite *sp_title = New_TSprite(frame, "images/bomberman_logo_title.png", pos_title);

    SDL_Rect pos_button_host = {(WIN_WIDTH / 2) - (410 / 2), 250, 410, 64};
    TButton *btn_host = New_TButton(frame, "images/button_host_normal.png", "images/button_host_hover.png", pos_button_host);
    btn_host->On_Click = On_Click_Host_Button;

    SDL_Rect pos_button_join = {(WIN_WIDTH / 2) - (410 / 2), (pos_button_host.y + pos_button_host.h)+15, 410, 64};
    TButton *btn_join = New_TButton(frame, "images/button_connect_normal.png", "images/button_connect_hover.png", pos_button_join);
    btn_join->On_Click = On_Click_Join_Button;

    SDL_Rect pos_button_quit = {(WIN_WIDTH / 2) - (410 / 2), (pos_button_join.y + pos_button_join.h)+15, 410, 64};
    TButton *btn_quit = New_TButton(frame, "images/button_quit_normal.png", "images/button_quit_hover.png", pos_button_quit);
    btn_quit->On_Click = On_Click_Quit_Button;

    frame->Add_Drawable(frame, (TDrawable*)sp_bg, "BG", 999);
    frame->Add_Drawable(frame, (TDrawable*)sp_title, "TITLE", 998);
    frame->Add_Drawable(frame, (TDrawable*)btn_host, "BTN_HOST", 1);
    frame->Add_Drawable(frame, (TDrawable*)btn_join, "BTN_JOIN", 1);
    frame->Add_Drawable(frame, (TDrawable*)btn_quit, "BTN_QUIT", 1);
}

static void On_Load(TFrame* frame, int argc, va_list args)
{
    if (IS_DEBUG)
        printf("Frame [%s]: On_Load method called | Args: [%d] %p\n", frame->frame_id, argc, &args);

    TButton *btn_host = (TButton*)frame->Get_Drawable(frame, "BTN_HOST");
    TButton *btn_join = (TButton*)frame->Get_Drawable(frame, "BTN_JOIN");
    TButton *btn_quit = (TButton*)frame->Get_Drawable(frame, "BTN_QUIT");

    btn_host->state = BUTTON_NORMAL;
    btn_join->state = BUTTON_NORMAL;
    btn_quit->state = BUTTON_NORMAL;
}

static void On_Event(TFrame* frame, SDL_Event event)
{
    TButton *btn_host = (TButton*)frame->Get_Drawable(frame, "BTN_HOST");
    TButton *btn_join = (TButton*)frame->Get_Drawable(frame, "BTN_JOIN");
    TButton *btn_quit = (TButton*)frame->Get_Drawable(frame, "BTN_QUIT");

    btn_host->Event_Handler(btn_host, frame, event);
    btn_join->Event_Handler(btn_join, frame, event);
    btn_quit->Event_Handler(btn_quit, frame, event);
}

static void On_Click_Host_Button(TButton *button, TFrame *frame)
{
    if (IS_DEBUG)
        printf("Button [%p]: Host Button pressed!\n", button);
    frame->window->Show_Frame(frame->window, "FRAME_HOST_MENU", 0);
}

static void On_Click_Join_Button(TButton *button, TFrame *frame)
{
    if (IS_DEBUG)
        printf("Button [%p]: Join Button pressed!\n", button);
    frame->window->Show_Frame(frame->window, "FRAME_JOIN_MENU", 0);
}

static void On_Click_Quit_Button(TButton *button, TFrame *frame)
{
    if (IS_DEBUG)
        printf("Button [%p]: Quit Button pressed!\n", button);
    frame->window->finished = 1;
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
}

static void Finish(TFrame* frame)
{
    if (IS_DEBUG)
        printf("Frame [%s]: Finish method called\n", frame->frame_id);
}

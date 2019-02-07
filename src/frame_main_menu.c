/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the main menu frame.
*/

#include "frame_main_menu.h"
#include "main.h"

static void Init(TFrame* frame, TWindow *window);
static void On_Load(TFrame* frame, TWindow *window, va_list args);
static void On_Event(TFrame* frame, TWindow *window, SDL_Event event);
static void On_Tick(TFrame* frame, TWindow *window);
static void On_Unload(TFrame* frame, TWindow *window);
static void Finish(TFrame* frame, TWindow *window);

static void On_Click_Host_Button(TButton *button, TWindow *window);
static void On_Click_Join_Button(TButton *button, TWindow *window);
static void On_Click_Quit_Button(TButton *button, TWindow *window);

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

static void Init(TFrame* frame, TWindow *window)
{
    SDL_Rect size_sprite_bg = {0, 0, 1280, 720};
    SDL_Rect pos_sprite_bg = {0, 0, 1280, 720};
    //TAnimatedSprite *sp_bg = New_TAnimatedSprite(window, "images/animated_background.png", size_sprite_bg, pos_sprite_bg , 52, -1);
    TAnimatedSprites *sp_bg = New_TAnimatedSprites(window, "images/mainmenu/fire%02d.png", 47, size_sprite_bg, pos_sprite_bg , 20, -1);

    SDL_Rect pos_title = {(WIN_WIDTH / 2) - (644 / 2), 100, 644, 104};
    TSprite *sp_title = New_TSprite(window, "images/bomberman_logo_title.png", pos_title);

    SDL_Rect pos_button_host = {(WIN_WIDTH / 2) - (410 / 2), 250, 410, 64};
    TButton *btn_host = New_TButton("images/button_host_normal.png", "images/button_host_hover.png", pos_button_host, window);
    btn_host->On_Click = On_Click_Host_Button;

    SDL_Rect pos_button_join = {(WIN_WIDTH / 2) - (410 / 2), (pos_button_host.y + pos_button_host.h)+15, 410, 64};
    TButton *btn_join = New_TButton("images/button_connect_normal.png", "images/button_connect_hover.png", pos_button_join, window);
    btn_join->On_Click = On_Click_Join_Button;

    SDL_Rect pos_button_quit = {(WIN_WIDTH / 2) - (410 / 2), (pos_button_join.y + pos_button_join.h)+15, 410, 64};
    TButton *btn_quit = New_TButton("images/button_quit_normal.png", "images/button_quit_hover.png", pos_button_quit, window);
    btn_quit->On_Click = On_Click_Quit_Button;

    frame->Add_Drawable(frame, (TDrawable*)sp_bg, "BG", 999);
    frame->Add_Drawable(frame, (TDrawable*)sp_title, "TITLE", 998);
    frame->Add_Drawable(frame, (TDrawable*)btn_host, "BTN_HOST", 1);
    frame->Add_Drawable(frame, (TDrawable*)btn_join, "BTN_JOIN", 1);
    frame->Add_Drawable(frame, (TDrawable*)btn_quit, "BTN_QUIT", 1);
}

static void On_Load(TFrame* frame, TWindow *window, va_list args)
{
    if (IS_DEBUG)
        printf("Frame [%s]: On_Load method called | Window finished: %d, %p\n", frame->frame_id, window->finished, &args);

    TButton *btn_host = (TButton*)frame->Get_Drawable(frame, "BTN_HOST");
    TButton *btn_join = (TButton*)frame->Get_Drawable(frame, "BTN_JOIN");
    TButton *btn_quit = (TButton*)frame->Get_Drawable(frame, "BTN_QUIT");

    btn_host->state = BUTTON_NORMAL;
    btn_join->state = BUTTON_NORMAL;
    btn_quit->state = BUTTON_NORMAL;
}

static void On_Event(TFrame* frame, TWindow *window, SDL_Event event)
{
    TButton *btn_host = (TButton*)frame->Get_Drawable(frame, "BTN_HOST");
    TButton *btn_join = (TButton*)frame->Get_Drawable(frame, "BTN_JOIN");
    TButton *btn_quit = (TButton*)frame->Get_Drawable(frame, "BTN_QUIT");

    btn_host->Event_Handler(btn_host, window, event);
    btn_join->Event_Handler(btn_join, window, event);
    btn_quit->Event_Handler(btn_quit, window, event);
}

static void On_Click_Host_Button(TButton *button, TWindow *window)
{
    if (IS_DEBUG)
        printf("Button [%p]: Host Button pressed!\n", button);
    window->Show_Frame(window, "FRAME_HOST_MENU", 0);
}

static void On_Click_Join_Button(TButton *button, TWindow *window)
{
    if (IS_DEBUG)
        printf("Button [%p]: Join Button pressed!\n", button);
    window->Show_Frame(window, "FRAME_JOIN_MENU", 0);
}

static void On_Click_Quit_Button(TButton *button, TWindow *window)
{
    if (IS_DEBUG)
        printf("Button [%p]: Quit Button pressed!\n", button);
    window->finished = 1;
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
}

static void Finish(TFrame* frame, TWindow *window)
{
    if (IS_DEBUG)
        printf("Frame [%s]: Finish method called | Window finished: %d\n", frame->frame_id, window->finished);
}

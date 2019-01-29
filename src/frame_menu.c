#include "frame_menu.h"
#include "main.h"

static void Init(TFrame* frame, TWindow *window);
static void On_Load(TFrame* frame, TWindow *window, va_list args);
static void On_Event(TFrame* frame, TWindow *window, SDL_Event event);
static void On_Tick(TFrame* frame, TWindow *window);
static void On_Unload(TFrame* frame, TWindow *window);
static void Finish(TFrame* frame, TWindow *window);

static char *ptr_username;

static void On_Click_Start_Button(TButton *button, TWindow *window);
static void On_Click_Quit_Button(TButton *button, TWindow *window);

TFrame* New_MenuFrame(void)
{
    TFrame *frm = New_TFrame("FRAME_MENU");
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
    //SDL_Color color = {255, 255, 255, 255};
    printf("Frame [%s]: Init method called | Window finished: %d\n", frame->frame_id, window->finished);

    // Background image
    // 17 because there is 17 frames
    SDL_Rect pos_sprite_bg = {0, 0, 430, 242};
    SDL_Rect size_sprite_bg = {0, 0, 1280, 720};
    //TSprite *sp_bg = New_TSprite(window, "images/bomberman_main_menu.png", pos_sprite_bg);
    TAnimatedSprite *sp_bg = New_TAnimatedSprite(window, "images/animated_background.png", pos_sprite_bg, size_sprite_bg, 50);

    /*
    SDL_Rect pos = {(WIN_WIDTH / 2) - (400 / 2), 20, 400, 92};
    TInput *input_username = New_TInput("images/input.png", pos, window, color);
    ptr_username = (input_username->text);

    SDL_Rect pos2 = {(WIN_WIDTH / 2) - (400 / 2), (pos.y + pos.h) + 20, 400, 92};
    TInput *input_serverip = New_TInput("images/input.png", pos2, window, color);

    SDL_Rect pos3 = {(WIN_WIDTH / 2) - (400 / 2), (pos2.y + pos2.h) + 20, 400, 92};
    TInput *input_port = New_TInput("images/input.png", pos3, window, color); */

    // Title image
    SDL_Rect pos_title = {(WIN_WIDTH / 2) - (644 / 2), 100, 644, 104};
    TSprite *sp_title = New_TSprite(window, "images/bomberman_logo_title.png", pos_title);

    // Host button
    SDL_Rect pos_button_host = {(WIN_WIDTH / 2) - (410 / 2), 250, 410, 64};
    TButton *btn_start = New_TButton("images/button_host_normal.png", "images/button_host_hover.png", pos_button_host, window);
    btn_start->On_Click = On_Click_Start_Button;

    // Join button
    SDL_Rect pos_button_join = {(WIN_WIDTH / 2) - (410 / 2), (pos_button_host.y + pos_button_host.h)+15, 410, 64};
    TButton *btn_join = New_TButton("images/button_connect_normal.png", "images/button_connect_hover.png", pos_button_join, window);
    btn_join->On_Click = On_Click_Start_Button;

    // Exit button
    SDL_Rect pos_button_quit = {(WIN_WIDTH / 2) - (410 / 2), (pos_button_join.y + pos_button_join.h)+15, 410, 64};
    TButton *btn_quit = New_TButton("images/button_quit_normal.png", "images/button_quit_hover.png", pos_button_quit, window);
    btn_quit->On_Click = On_Click_Quit_Button;

    frame->Add_Drawable(frame, (void*)sp_bg, ANIMATED_SPRITE, "BG", 999);
    frame->Add_Drawable(frame, (void*)sp_title, SPRITE, "TITLE", 998);
    /*frame->Add_Drawable(frame, (void*)input_username, INPUT, "INPUT_USER", 1);
    frame->Add_Drawable(frame, (void*)input_serverip, INPUT, "INPUT_SERV", 1);
    frame->Add_Drawable(frame, (void*)input_port, INPUT, "INPUT_PORT", 1);*/
    frame->Add_Drawable(frame, (void*)btn_start, BUTTON, "BTN_START", 1);
    frame->Add_Drawable(frame, (void*)btn_join, BUTTON, "BTN_JOIN", 1);
    frame->Add_Drawable(frame, (void*)btn_quit, BUTTON, "BTN_QUIT", 1);
}

static void On_Load(TFrame* frame, TWindow *window, va_list args)
{
    /*TInput *input_username = (TInput*)frame->Get_Drawable(frame, "INPUT_USER");
    TInput *input_serverip = (TInput*)frame->Get_Drawable(frame, "INPUT_SERV");
    TInput *input_port = (TInput*)frame->Get_Drawable(frame, "INPUT_PORT");*/
    TButton *btn_start = (TButton*)frame->Get_Drawable(frame, "BTN_START");
    TButton *btn_join = (TButton*)frame->Get_Drawable(frame, "BTN_JOIN");
    TButton *btn_quit = (TButton*)frame->Get_Drawable(frame, "BTN_QUIT");

    printf("Frame [%s]: On_Load method called | Window finished: %d, %p\n", frame->frame_id, window->finished, &args);

    SDL_StartTextInput();

    btn_start->state = BUTTON_NORMAL;
    btn_join->state = BUTTON_NORMAL;
    btn_quit->state = BUTTON_NORMAL;
    /*strcpy(input_username->text, "");
    strcpy(input_serverip->text, "");
    strcpy(input_port->text, "");*/
    SDL_SetRenderDrawColor(window->renderer_window, 0, 255, 0, 255);
}

static void On_Event(TFrame* frame, TWindow *window, SDL_Event event)
{
    /*TInput *input_username = (TInput*)frame->Get_Drawable(frame, "INPUT_USER");
    TInput *input_serverip = (TInput*)frame->Get_Drawable(frame, "INPUT_SERV");
    TInput *input_port = (TInput*)frame->Get_Drawable(frame, "INPUT_PORT");*/
    TButton *btn_start = (TButton*)frame->Get_Drawable(frame, "BTN_START");
    TButton *btn_join = (TButton*)frame->Get_Drawable(frame, "BTN_JOIN");
    TButton *btn_quit = (TButton*)frame->Get_Drawable(frame, "BTN_QUIT");

    btn_start->Event_Handler(btn_start, window, event);
    btn_join->Event_Handler(btn_join, window, event);
    btn_quit->Event_Handler(btn_quit, window, event);
    /*input_username->Event_Handler(input_username, window, event);
    input_serverip->Event_Handler(input_serverip, window, event);
    input_port->Event_Handler(input_port, window, event);*/
    if (event.type == SDL_KEYUP) {
        printf("Frame [%s]: On_Event method called with key released | Window finished: %d\n", frame->frame_id, window->finished);
        if (event.key.keysym.sym == SDLK_ESCAPE)
            window->finished = 1;
    }
}

static void On_Click_Start_Button(TButton *button, TWindow *window)
{
    printf("Button [%p]: Start Button pressed!\n", button);
    window->Show_Frame(window, "FRAME_GAME", 1, ptr_username);
}

static void On_Click_Quit_Button(TButton *button, TWindow *window)
{
    printf("Button [%p]: Quit Button pressed!\n", button);
    window->finished = 1;
}

static void On_Tick(TFrame* frame, TWindow *window)
{
    SDL_RenderClear(window->renderer_window);
    frame->Draw_Drawables(frame, window);
    SDL_RenderPresent(window->renderer_window);
    printf("Frame [%s]: On_Tick method called: %d | Window finished: %d\n", frame->frame_id, frame->initialized, window->finished);
}

static void On_Unload(TFrame* frame, TWindow *window)
{
    printf("Frame [%s]: On_Unload method called | Window finished: %d\n", frame->frame_id, window->finished);
    SDL_StopTextInput();
}

static void Finish(TFrame* frame, TWindow *window)
{
    printf("Frame [%s]: Finish method called | Window finished: %d\n", frame->frame_id, window->finished);
}

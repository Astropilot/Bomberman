#include "frame_menu.h"

static void Init(TFrame* frame, TWindow *window);
static void On_Load(TFrame* frame, TWindow *window, va_list args);
static void On_Event(TFrame* frame, TWindow *window, SDL_Event event);
static void On_Tick(TFrame* frame, TWindow *window);
static void On_Unload(TFrame* frame, TWindow *window);
static void Finish(TFrame* frame, TWindow *window);

static char *ptr_username;

static void On_Click_Start_Button(TButton *button, TWindow *window);

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
    SDL_Color color = {255, 255, 255, 255};
    printf("Frame [%s]: Init method called | Window finished: %d\n", frame->frame_id, window->finished);

    SDL_Rect pos = {(700 / 2) - (400 / 2), 20, 400, 92};
    TInput *input_username = New_TInput("images/input.png", pos, window, color);
    ptr_username = (input_username->text);

    SDL_Rect pos2 = {(700 / 2) - (400 / 2), (pos.y + pos.h) + 20, 400, 92};
    TInput *input_serverip = New_TInput("images/input.png", pos2, window, color);

    SDL_Rect pos3 = {(700 / 2) - (400 / 2), (pos2.y + pos2.h) + 20, 400, 92};
    TInput *input_port = New_TInput("images/input.png", pos3, window, color);

    SDL_Rect pos4 = {(700 / 2) - (364 / 2), (pos3.y + pos3.h) + 50, 364, 182};
    TButton *btn_start = New_TButton("images/btn_s.png", "images/btn_hs.png", pos4, window);
    btn_start->On_Click = On_Click_Start_Button;

    frame->Add_Drawable(frame, (void*)input_username, INPUT, "INPUT_USER", 1);
    frame->Add_Drawable(frame, (void*)input_serverip, INPUT, "INPUT_SERV", 1);
    frame->Add_Drawable(frame, (void*)input_port, INPUT, "INPUT_PORT", 1);
    frame->Add_Drawable(frame, (void*)btn_start, BUTTON, "BTN_START", 1);
}

static void On_Load(TFrame* frame, TWindow *window, va_list args)
{
    TInput *input_username = (TInput*)frame->Get_Drawable(frame, "INPUT_USER");
    TInput *input_serverip = (TInput*)frame->Get_Drawable(frame, "INPUT_SERV");
    TInput *input_port = (TInput*)frame->Get_Drawable(frame, "INPUT_PORT");
    TButton *btn_start = (TButton*)frame->Get_Drawable(frame, "BTN_START");

    printf("Frame [%s]: On_Load method called | Window finished: %d, %p\n", frame->frame_id, window->finished, &args);

    SDL_StartTextInput();

    btn_start->state = BUTTON_NORMAL;
    strcpy(input_username->text, "");
    strcpy(input_serverip->text, "");
    strcpy(input_port->text, "");
    SDL_SetRenderDrawColor(window->renderer_window, 0, 255, 0, 255);
}

static void On_Event(TFrame* frame, TWindow *window, SDL_Event event)
{
    TInput *input_username = (TInput*)frame->Get_Drawable(frame, "INPUT_USER");
    TInput *input_serverip = (TInput*)frame->Get_Drawable(frame, "INPUT_SERV");
    TInput *input_port = (TInput*)frame->Get_Drawable(frame, "INPUT_PORT");
    TButton *btn_start = (TButton*)frame->Get_Drawable(frame, "BTN_START");

    btn_start->Event_Handler(btn_start, window, event);
    input_username->Event_Handler(input_username, window, event);
    input_serverip->Event_Handler(input_serverip, window, event);
    input_port->Event_Handler(input_port, window, event);
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

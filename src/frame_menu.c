#include "frame_menu.h"

static void Init(TFrame* frame, TWindow *window);
static void On_Load(TFrame* frame, TWindow *window);
static void On_Event(TFrame* frame, TWindow *window, SDL_Event event);
static void On_Tick(TFrame* frame, TWindow *window);
static void On_Unload(TFrame* frame, TWindow *window);
static void Finish(TFrame* frame, TWindow *window);

static void On_Click_Start_Button(TButton *button, TWindow *window);

static SDL_Texture *t_text;
static SDL_Rect pos;
static TButton *btn_start;

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
    printf("Frame [%s]: Init method called | Window finished: %d\n", frame->frame_id, window->finished);
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *s_text = NULL;

    s_text = TTF_RenderText_Solid(TTF_OpenFont("fonts/fixedsys.ttf", 18), "Appuyez sur <ESPACE> pour commencer.", color);
    t_text = SDL_CreateTextureFromSurface(window->renderer_window, s_text);

    pos.x = (600 / 2) - 50;
    pos.y = 150;
    pos.w = 364;
    pos.h = 182;
    btn_start = New_TButton("images/btn_s.png", "images/btn_hs.png", pos, window);
    btn_start->On_Click = On_Click_Start_Button;

    pos.x = (600 / 2) - 100;
    pos.y = 50;
    pos.w = s_text->w;
    pos.h = s_text->h;
    free(s_text);
}

static void On_Load(TFrame* frame, TWindow *window)
{
    printf("Frame [%s]: On_Load method called | Window finished: %d\n", frame->frame_id, window->finished);

    // On définit la couleur de fond de la fenêtre.
    btn_start->state = BUTTON_NORMAL;
    SDL_SetRenderDrawColor(window->renderer_window, 0, 255, 0, 255);
}

static void On_Event(TFrame* frame, TWindow *window, SDL_Event event)
{
    btn_start->Event_Handler(btn_start, window, event);
    if (event.type == SDL_KEYUP) {
        printf("Frame [%s]: On_Event method called with key released | Window finished: %d\n", frame->frame_id, window->finished);
        if (event.key.keysym.sym == SDLK_SPACE)
            window->Show_Frame(window, "FRAME_GAME");
        if (event.key.keysym.sym == SDLK_ESCAPE)
            window->finished = 1;
    }
}

static void On_Click_Start_Button(TButton *button, TWindow *window)
{
    printf("Button [%p]: Start Button pressed!\n", button);
    window->Show_Frame(window, "FRAME_GAME");
}

static void On_Tick(TFrame* frame, TWindow *window)
{
    SDL_RenderClear(window->renderer_window);
    btn_start->Draw(btn_start, window);
    SDL_RenderCopy(window->renderer_window, t_text, NULL, &pos);
    SDL_RenderPresent(window->renderer_window);
    printf("Frame [%s]: On_Tick method called: %d | Window finished: %d\n", frame->frame_id, frame->initialized, window->finished);
}

static void On_Unload(TFrame* frame, TWindow *window)
{
    printf("Frame [%s]: On_Unload method called | Window finished: %d\n", frame->frame_id, window->finished);
}

static void Finish(TFrame* frame, TWindow *window)
{
    printf("Frame [%s]: Finish method called | Window finished: %d\n", frame->frame_id, window->finished);
    btn_start->Free(btn_start);
    SDL_DestroyTexture(t_text);
}

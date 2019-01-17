#include "window.h"

static void TWindow_Init(TWindow *this);
static void TWindow_Free_Frames(TWindow *this);
static void TWindow_Finish_Frames(TWindow *this);
static void TWindow_Loop(TWindow *this);

TWindow* New_TWindow(void)
{
       TWindow *this = malloc(sizeof(TWindow));

       if(!this) return NULL;
       TWindow_Init(this);
       this->Free = TWindow_New_Free;
       return this;
}

static void TWindow_Init(TWindow *this)
{
       this->Create_Window = TWindow_Create_Window;
       this->Add_Frame = TWindow_Add_Frame;
       this->Show_Frame = TWindow_Show_Frame;
       this->Wait_Quit = TWindow_Wait_Quit;
       this->screen_window = NULL;
       this->renderer_window = NULL;
       this->finished = 0;
       this->frames_head = NULL;
       this->shown_frame = NULL;
}

static void TWindow_Free_Frames(TWindow *this)
{
    TFrame_Node *current = this->frames_head;
    TFrame_Node *tmp = NULL;

    while (current != NULL) {
        current->frame->Free(current->frame);

        tmp = current;
        current = current->next;
        free(tmp);
    }
}

static void TWindow_Finish_Frames(TWindow *this)
{
    TFrame_Node *current = this->frames_head;

    while (current != NULL) {
        current->frame->Finish(current->frame, this);
        current = current->next;
    }
}

static void TWindow_Loop(TWindow *this)
{
    SDL_Event event;
    unsigned int current_time = 0;
    unsigned int last_time = 0;

    printf("In game loop!\n");

    while (!this->finished) {
        while( SDL_PollEvent( &event ) != 0 ) {
            if( event.type == SDL_QUIT )
                this->finished = 1;
            else {
                if (this->shown_frame)
                    this->shown_frame->On_Event(this->shown_frame, this, event);
            }
        }
        if (this->shown_frame) {
            current_time = SDL_GetTicks();
            if (current_time > last_time + 50) {
                this->shown_frame->On_Tick(this->shown_frame, this);
                last_time = current_time;
            }
        }
    }
    TWindow_Finish_Frames(this);
    return;
}

int TWindow_Create_Window(TWindow *this, const char *title, int width, int height, const char *frame_id)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        printf("Error while loading game window (SDL)!\n");
        return (0);
    }

    this->screen_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    width,
                                    height,
                                    SDL_WINDOW_SHOWN);
    if (this->screen_window == NULL) {
        printf("Error while loading game window (SDL)!\n");
        return (0);
    }
    this->renderer_window = SDL_CreateRenderer(this->screen_window, -1, SDL_RENDERER_ACCELERATED);
    if (this->renderer_window == NULL) {
        printf("Error while loading game window (SDL)!\n");
        return (0);
    }
    IMG_Init(IMG_INIT_PNG);

    if(TTF_Init()==-1) {
        printf("Error while loading TTF (SDL)!\n");
        return (0);
    }

    TWindow_Show_Frame(this, frame_id);
    TWindow_Loop(this);

    return (1);
}

void TWindow_Add_Frame(TWindow *this, TFrame *frame)
{
    if (!this->frames_head) {
        TFrame_Node *frame_node = malloc(sizeof(TFrame_Node));

        frame_node->frame = frame;
        frame_node->next = NULL;
        this->frames_head = frame_node;
    } else {
        TFrame_Node *current = this->frames_head;

        while (current->next != NULL)
            current = current->next;
        current->next = malloc(sizeof(TFrame_Node));
        current->next->frame = frame;
        current->next->next = NULL;
    }
}

void TWindow_Show_Frame(TWindow *this, const char *frame_id)
{
    TFrame_Node *current = this->frames_head;
    while (current != NULL) {
        if (strcmp(current->frame->frame_id, frame_id) == 0) {
            printf("Frame [%s] trouvée, prêt à l'affichage !\n", frame_id);
            if (this->shown_frame) {
                this->shown_frame->Finish(this->shown_frame, this);
            }
            if (!current->frame->initialized)
                current->frame->Init(current->frame, this);
            current->frame->On_Load(current->frame, this);
            this->shown_frame = current->frame;
            return;
        }
        current = current->next;
    }
    printf("Frame [%s] non trouvée !\n", frame_id);
}

void TWindow_Wait_Quit(TWindow *this)
{
    while (!this->finished);
}

void TWindow_New_Free(TWindow *this)
{
    if (this) {
        TWindow_Free_Frames(this);
        IMG_Quit();
        SDL_DestroyRenderer(this->renderer_window);
        SDL_DestroyWindow(this->screen_window);
        SDL_Quit();
    }
    free(this);
}

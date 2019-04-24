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

#include "main.h"
#include "glib.h"
#include "ui/scene_host_menu.h"

static void On_Init(TScene *scene);
static void On_Load(TScene *scene, int argc, va_list args);
static void On_Event(TScene *scene, SDL_Event event);
static void On_Tick(TScene *scene);
static void On_Unload(TScene *scene);
static void On_Finish(TScene *scene);

static void On_Click_Play_Button(TButton *button, TScene *scene);
static void On_MinValueChange(TSlider *slider, TScene *scene, int value);
static void On_MaxValueChange(TSlider *slider, TScene *scene, int value);
static void On_WallsValueChange(TSlider *slider, TScene *scene, int value);
static void On_ExtraValueChange(TSlider *slider, TScene *scene, int value);

TScene* New_HostMenuScene(void)
{
    TScene *frm = New_TScene("SCENE_HOST_MENU");
    if (frm) {
        frm->On_Init = On_Init;
        frm->On_Load = On_Load;
        frm->On_Event = On_Event;
        frm->On_Tick = On_Tick;
        frm->On_Unload = On_Unload;
        frm->On_Finish = On_Finish;
    }
    return (frm);
}

static void On_Init(TScene* scene)
{
    TTF_Font *font = NULL;
    SDL_Color color = {255, 255, 255, 255};
    SDL_Rect pos_sprite_bg = {0, 0, 430, 242};
    SDL_Rect size_sprite_bg = {0, 0, 1280, 720};
    TAnimatedSprite *sp_bg = New_TAnimatedSprite(scene,
        RES_PATH "animated_background.png", pos_sprite_bg,
        size_sprite_bg, 52, -1
    );

    SDL_Rect pos_title = {(WIN_WIDTH / 2) - (644 / 2), 100, 644, 104};
    TSprite *sp_title = New_TSprite(scene,
        RES_PATH "bomberman_logo_title.png", pos_title
    );

    SDL_Rect pos = {(WIN_WIDTH / 2) - (400 / 2), 250, 400, 92};
    TSprite *sprite_input_username = New_TSprite(scene, RES_PATH "input.png", pos);
    font = loadFont(FONT_PATH "fixedsys.ttf", 24);
    TInput *input_username = New_TInput(scene, sprite_input_username,
        color, 15, "Username", font
    );

    SDL_Rect pos2 = {(WIN_WIDTH / 2) - (400 / 2), (pos.y + pos.h) + 15, 400, 92};
    TSprite *sprite_input_serverport = New_TSprite(scene, RES_PATH "input.png", pos2);
    font = loadFont(FONT_PATH "fixedsys.ttf", 24);
    TInput *input_serverport = New_TInput(scene, sprite_input_serverport,
        color, 5, "Server port", font
    );

    SDL_Rect pos_button_play = {(WIN_WIDTH / 2) - (410 / 2), WIN_HEIGHT - 64 - 15, 410, 64};
    TButton *btn_play = New_TButton(scene,
        RES_PATH "button_create_normal.png",
        RES_PATH "button_create_hover.png", pos_button_play
    );
    btn_play->On_Click = On_Click_Play_Button;

    SDL_Rect pos_txt_slider = {0, 0, 0, 0};
    SDL_Point size_btn = {10, 20};
    SDL_Rect pos_slidermin = {(WIN_WIDTH / 2) - (410 / 2), (pos2.y + pos2.h) + 15, 410, 20};
    TSlider *slider_min = New_TSlider(scene,
        RES_PATH "slider_bg.png", RES_PATH "slider.png",
        pos_slidermin, size_btn, 2, 4, 2
    );
    slider_min->On_ValueChange = On_MinValueChange;

    font = loadFont(FONT_PATH "fixedsys.ttf", 24);
    TText *txt_slider_min = New_TText(scene, "Minimum de joueurs: 2", font, color, pos_txt_slider);
    txt_slider_min->pos.x = pos_slidermin.x - (txt_slider_min->pos.w) - 5;
    txt_slider_min->pos.y = pos_slidermin.y;

    SDL_Rect pos_slidermax = {(WIN_WIDTH / 2) - (410 / 2), (pos_slidermin.y + pos_slidermin.h) + 15, 410, 20};
    TSlider *slider_max = New_TSlider(scene,
        RES_PATH "slider_bg.png", RES_PATH "slider.png",
        pos_slidermax, size_btn, 2, 4, 4
    );
    slider_max->On_ValueChange = On_MaxValueChange;

    font = loadFont(FONT_PATH "fixedsys.ttf", 24);
    TText *txt_slider_max = New_TText(scene, "Maximum de joueurs: 4", font, color, pos_txt_slider);
    txt_slider_max->pos.x = pos_slidermax.x - (txt_slider_max->pos.w) - 5;
    txt_slider_max->pos.y = pos_slidermax.y;

    SDL_Rect pos_sliderwalls = {(WIN_WIDTH / 2) - (410 / 2), (pos_slidermax.y + pos_slidermax.h) + 15, 410, 20};
    TSlider *slider_walls = New_TSlider(scene,
        RES_PATH "slider_bg.png", RES_PATH "slider.png",
        pos_sliderwalls, size_btn, 0, 100, 40
    );
    slider_walls->On_ValueChange = On_WallsValueChange;

    font = loadFont(FONT_PATH "fixedsys.ttf", 24);
    TText *txt_slider_walls = New_TText(scene, "Taux caisses: 40%", font, color, pos_txt_slider);
    txt_slider_walls->pos.x = pos_sliderwalls.x - (txt_slider_walls->pos.w) - 5;
    txt_slider_walls->pos.y = pos_sliderwalls.y;

    SDL_Rect pos_sliderextra = {(WIN_WIDTH / 2) - (410 / 2), (pos_sliderwalls.y + pos_sliderwalls.h) + 15, 410, 20};
    TSlider *slider_extra = New_TSlider(scene,
        RES_PATH "slider_bg.png", RES_PATH "slider.png",
        pos_sliderextra, size_btn, 0, 100, 90
    );
    slider_extra->On_ValueChange = On_ExtraValueChange;

    font = loadFont(FONT_PATH "fixedsys.ttf", 24);
    TText *txt_slider_extra = New_TText(scene, "Taux d'extras: 90%", font, color, pos_txt_slider);
    txt_slider_extra->pos.x = pos_sliderextra.x - (txt_slider_extra->pos.w) - 5;
    txt_slider_extra->pos.y = pos_sliderextra.y;

    scene->Add_Drawable(scene, (TDrawable*)slider_min,
        "SLIDER_MIN", 1, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)txt_slider_min,
        "LABEL_SLIDER_MIN", 1, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)slider_max,
        "SLIDER_MAX", 1, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)txt_slider_max,
        "LABEL_SLIDER_MAX", 1, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)slider_walls,
        "SLIDER_WALLS", 1, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)txt_slider_walls,
        "LABEL_SLIDER_WALLS", 1, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)slider_extra,
        "SLIDER_EXTRA", 1, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)txt_slider_extra,
        "LABEL_SLIDER_EXTRA", 1, GLIB_FREE_ON_FINISH
    );


    scene->Add_Drawable(scene, (TDrawable*)sp_bg,
        "BG", 999, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)sp_title,
        "TITLE", 998, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)input_username,
        "INPUT_USER", 1, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)input_serverport,
        "INPUT_PORT", 1, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)btn_play,
        "BTN_PLAY", 1, GLIB_FREE_ON_FINISH
    );
}

static void On_MinValueChange(TSlider *slider, TScene *scene, int value)
{
    TText *label_slider_min = (TText*)scene->Get_Drawable(scene, "LABEL_SLIDER_MIN");
    char *status = malloc(sizeof(char) * 255);

    sprintf(status, "Minimum de joueurs: %d", value);
    label_slider_min->Change_Text(label_slider_min, scene, status);
    label_slider_min->pos.x = slider->pos.x - (label_slider_min->pos.w) - 5;
    label_slider_min->pos.y = slider->pos.y;

    free(status);
}

static void On_MaxValueChange(TSlider *slider, TScene *scene, int value)
{
    TText *label_slider_max = (TText*)scene->Get_Drawable(scene, "LABEL_SLIDER_MAX");
    char *status = malloc(sizeof(char) * 255);

    sprintf(status, "Maximum de joueurs: %d", value);
    label_slider_max->Change_Text(label_slider_max, scene, status);
    label_slider_max->pos.x = slider->pos.x - (label_slider_max->pos.w) - 5;
    label_slider_max->pos.y = slider->pos.y;

    free(status);
}

static void On_WallsValueChange(TSlider *slider, TScene *scene, int value)
{
    TText *label_slider_walls = (TText*)scene->Get_Drawable(scene, "LABEL_SLIDER_WALLS");
    char *status = malloc(sizeof(char) * 255);

    sprintf(status, "Murs cassables: %d%%", value);
    label_slider_walls->Change_Text(label_slider_walls, scene, status);
    label_slider_walls->pos.x = slider->pos.x - (label_slider_walls->pos.w) - 5;
    label_slider_walls->pos.y = slider->pos.y;

    free(status);
}

static void On_ExtraValueChange(TSlider *slider, TScene *scene, int value)
{
    TText *label_slider_extra = (TText*)scene->Get_Drawable(scene, "LABEL_SLIDER_EXTRA");
    char *status = malloc(sizeof(char) * 255);

    sprintf(status, "Taux d'extras: %d%%", value);
    label_slider_extra->Change_Text(label_slider_extra, scene, status);
    label_slider_extra->pos.x = slider->pos.x - (label_slider_extra->pos.w) - 5;
    label_slider_extra->pos.y = slider->pos.y;

    free(status);
}

static void On_Load(TScene* scene, int argc, va_list args)
{
    if (IS_DEBUG)
        printf("Scene [%s]: On_Load method called | Args: [%d] %p\n", scene->scene_id, argc, &args);
    TInput *input_username = (TInput*)scene->Get_Drawable(scene, "INPUT_USER");
    TInput *input_serverport = (TInput*)scene->Get_Drawable(scene, "INPUT_PORT");
    TButton *btn_play = (TButton*)scene->Get_Drawable(scene, "BTN_PLAY");
    TSlider *slider_min = (TSlider*)scene->Get_Drawable(scene, "SLIDER_MIN");
    TText *label_slider_min = (TText*)scene->Get_Drawable(scene, "LABEL_SLIDER_MIN");
    TSlider *slider_max = (TSlider*)scene->Get_Drawable(scene, "SLIDER_MAX");
    TText *label_slider_max = (TText*)scene->Get_Drawable(scene, "LABEL_SLIDER_MAX");
    TSlider *slider_walls = (TSlider*)scene->Get_Drawable(scene, "SLIDER_WALLS");
    TText *label_slider_walls = (TText*)scene->Get_Drawable(scene, "LABEL_SLIDER_WALLS");
    TSlider *slider_extra = (TSlider*)scene->Get_Drawable(scene, "SLIDER_EXTRA");
    TText *label_slider_extra = (TText*)scene->Get_Drawable(scene, "LABEL_SLIDER_EXTRA");

    SDL_StartTextInput();

    btn_play->state = BUTTON_NORMAL;
    strcpy(input_username->text, "");
    strcpy(input_serverport->text, "");

    slider_min->value = 2;
    label_slider_min->Change_Text(label_slider_min, scene, "Minimum de joueurs: 2");
    label_slider_min->pos.x = slider_min->pos.x - (label_slider_min->pos.w) - 5;
    label_slider_min->pos.y = slider_min->pos.y;
    slider_max->value = 4;
    label_slider_max->Change_Text(label_slider_max, scene, "Maximum de joueurs: 4");
    label_slider_max->pos.x = slider_max->pos.x - (label_slider_max->pos.w) - 5;
    label_slider_max->pos.y = slider_max->pos.y;
    slider_walls->value = 40;
    label_slider_walls->Change_Text(label_slider_walls, scene, "Murs cassables: 40%");
    label_slider_walls->pos.x = slider_walls->pos.x - (label_slider_walls->pos.w) - 5;
    label_slider_walls->pos.y = slider_walls->pos.y;
    slider_extra->value = 90;
    label_slider_extra->Change_Text(label_slider_extra, scene, "Taux d'extras: 90%");
    label_slider_extra->pos.x = slider_extra->pos.x - (label_slider_extra->pos.w) - 5;
    label_slider_extra->pos.y = slider_extra->pos.y;

    if (scene->Is_BackgroundMusic_Paused(scene) && scene->Is_BackgroundMusic_Playing(scene)) {
        scene->Resume_BackgroundMusic(scene);
    } else {
        scene->Play_BackgroundMusic(scene, SOUND_PATH "theme_bg.wav", -1);
    }
}

static void On_Event(TScene* scene, SDL_Event event)
{
    TInput *input_username = (TInput*)scene->Get_Drawable(scene, "INPUT_USER");
    TInput *input_serverport = (TInput*)scene->Get_Drawable(scene, "INPUT_PORT");
    TButton *btn_play = (TButton*)scene->Get_Drawable(scene, "BTN_PLAY");
    TSlider *slider_min = (TSlider*)scene->Get_Drawable(scene, "SLIDER_MIN");
    TSlider *slider_max = (TSlider*)scene->Get_Drawable(scene, "SLIDER_MAX");
    TSlider *slider_walls = (TSlider*)scene->Get_Drawable(scene, "SLIDER_WALLS");
    TSlider *slider_extra = (TSlider*)scene->Get_Drawable(scene, "SLIDER_EXTRA");

    btn_play->Event_Handler(btn_play, scene, event);
    input_username->Event_Handler(input_username, event);
    input_serverport->Event_Handler(input_serverport, event);
    slider_min->Event_Handler(slider_min, scene, event);
    slider_max->Event_Handler(slider_max, scene, event);
    slider_walls->Event_Handler(slider_walls, scene, event);
    slider_extra->Event_Handler(slider_extra, scene, event);
    if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_ESCAPE)
            scene->window->Show_Scene(scene->window, "SCENE_MAIN_MENU", 0);
    }
}

static void On_Click_Play_Button(TButton *button, TScene *scene)
{
    if (IS_DEBUG)
        printf("Button [%p]: Play Button pressed!\n", button);
    TInput *input_username = (TInput*)scene->Get_Drawable(scene, "INPUT_USER");
    TInput *input_port = (TInput*)scene->Get_Drawable(scene, "INPUT_PORT");

    if (strlen(input_username->text) > 0) {
        int port = atoi(input_port->text);
        lobby_args_t params = {input_username->text, NULL, port};
        scene->window->Show_Scene(scene->window, "SCENE_LOBBY", 1, params);
    }
}

static void On_Tick(TScene* scene)
{
    SDL_RenderClear(scene->window->renderer_window);
    scene->Draw_Drawables(scene);
    SDL_RenderPresent(scene->window->renderer_window);
}

static void On_Unload(TScene* scene)
{
    if (IS_DEBUG)
        printf("Scene [%s]: On_Unload method called\n", scene->scene_id);
    SDL_StopTextInput();
    scene->Pause_BackgroundMusic(scene, 0);
}

static void On_Finish(TScene* scene)
{
    if (IS_DEBUG)
        printf("Scene [%s]: Finish method called\n", scene->scene_id);
}

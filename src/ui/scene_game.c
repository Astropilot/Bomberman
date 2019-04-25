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
#include "core/player.h"
#include "ui/scene_game.h"
#include "network/game/client.h"

static void On_Init(TScene *scene);
static void On_Load(TScene *scene, int argc, va_list args);
static void On_Event(TScene *scene, SDL_Event event);
static void On_Tick(TScene *scene);
static void On_Unload(TScene *scene);
static void On_Finish(TScene *scene);

static TGameClient *gameclient;

TScene* New_GameScene(TGameClient *m_gameclient)
{
    TScene *frm = New_TScene("SCENE_GAME");
    if (frm) {
        frm->On_Init = On_Init;
        frm->On_Load = On_Load;
        frm->On_Event = On_Event;
        frm->On_Tick = On_Tick;
        frm->On_Unload = On_Unload;
        frm->On_Finish = On_Finish;
    }
    gameclient = m_gameclient;
    return (frm);
}

static void On_Init(TScene* scene)
{
    SDL_Rect pos_sprite2 = {0, 0, WIN_WIDTH, WIN_HEIGHT};
    TSprite *sp2 = New_TSprite(scene,
        RES_PATH "bomberman_game.png", pos_sprite2
    );

    scene->Add_Drawable(scene, (TDrawable*)sp2,
        "BG", 999, GLIB_FREE_ON_FINISH
    );
}

static void On_Load(TScene* scene, int argc, va_list args)
{
    if (IS_DEBUG)
        printf("Scene [%s]: On_Load method called | Argc: %d\n", scene->scene_id, argc);
    TClient *client = va_arg(args, TClient*);
    TGameServer *server = va_arg(args, TGameServer*);
    int player = va_arg(args, int);
    int nb_players = va_arg(args, int);
    int i;

    gameclient->client = client;
    if (server)
        gameclient->is_owner = 1;
    gameclient->gameserver = server;
    gameclient->player = player;

    SDL_Rect size = {0, 0, 64, 64};
    SDL_Rect pos = {0, 0, 32, 32};
    SDL_Rect health_pos = {0, 0, 32, 9};
    char *player_id = malloc(sizeof(char) * 255);
    for (i = 0; i < nb_players; i++) {
        TAnimatedSprites *sp_down = New_TAnimatedSprites(scene,
            CHAR_PATH "face%02d.png", 7, size, pos, 66, -1
        );
        TAnimatedSprites *sp_up = New_TAnimatedSprites(scene,
            CHAR_PATH "back%02d.png", 7, size, pos, 66, -1
        );
        TAnimatedSprites *sp_right = New_TAnimatedSprites(scene,
            CHAR_PATH "side_right%02d.png", 17, size, pos, 66, -1
        );
        TAnimatedSprites *sp_left = New_TAnimatedSprites(scene,
            CHAR_PATH "side_left%02d.png", 21, size, pos, 66, -1
        );
        TSprite *sp_health_bar_bg = New_TSprite(scene,
            CHAR_PATH "health_bg.png", health_pos
        );
        sprintf(player_id, CHAR_PATH "health_bar_%d.png", i);
        TSprite *sp_health_actual = New_TSprite(scene,
            player_id, health_pos
        );

        sprintf(player_id, "PLAYER_%d_%u", i, SOUTH);
        sp_down->is_visible = 0;
        scene->Add_Drawable(scene, (TDrawable*)sp_down,
            player_id, 1, GLIB_FREE_ON_UNLOAD
        );

        sprintf(player_id, "PLAYER_%d_%u", i, NORTH);
        sp_up->is_visible = 0;
        scene->Add_Drawable(scene, (TDrawable*)sp_up,
            player_id, 1, GLIB_FREE_ON_UNLOAD
        );

        sprintf(player_id, "PLAYER_%d_%u", i, EAST);
        sp_right->is_visible = 0;
        scene->Add_Drawable(scene, (TDrawable*)sp_right,
            player_id, 1, GLIB_FREE_ON_UNLOAD
        );

        sprintf(player_id, "PLAYER_%d_%u", i, WEST);
        sp_left->is_visible = 0;
        scene->Add_Drawable(scene, (TDrawable*)sp_left,
            player_id, 1, GLIB_FREE_ON_UNLOAD
        );

        sprintf(player_id, "PLAYER_%d_HPBG", i);
        scene->Add_Drawable(scene, (TDrawable*)sp_health_bar_bg,
            player_id, 1, GLIB_FREE_ON_UNLOAD
        );
        sprintf(player_id, "PLAYER_%d_HPBAR", i);
        scene->Add_Drawable(scene, (TDrawable*)sp_health_actual,
            player_id, 1, GLIB_FREE_ON_UNLOAD
        );
    }
    free(player_id);

    SDL_Rect size_minion = {0, 0, 850, 604};
    SDL_Rect pos_minion = {0, 0, 32, 23};
    TAnimatedSprites *sp_minion = New_TAnimatedSprites(scene,
        MINION_PATH "minion_%02d.png", 4, size_minion, pos_minion, 66, -1
    );
    sp_minion->is_visible = 0;
    scene->Add_Drawable(scene, (TDrawable*)sp_minion,
        "MINION", 2, GLIB_FREE_ON_UNLOAD
    );

    TSound *bomb_pose = New_TSound(scene, SOUND_PATH "bomb_pose.wav");
    TSound *bomb_explode = New_TSound(scene, SOUND_PATH "bomb_explode.wav");
    TSound *power_up = New_TSound(scene, SOUND_PATH "power_up.wav");
    scene->Add_Drawable(scene, (TDrawable*)bomb_pose,
        "BOMB_POSE", 999, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)bomb_explode,
        "BOMB_EXPLODE", 999, GLIB_FREE_ON_FINISH
    );
    scene->Add_Drawable(scene, (TDrawable*)power_up,
        "POWER_UP", 999, GLIB_FREE_ON_FINISH
    );

    if (scene->Is_BackgroundMusic_Playing(scene)) {
        scene->Pause_BackgroundMusic(scene, 1);
    }
    scene->Play_BackgroundMusic(scene, SOUND_PATH "game_bg.wav", -1);

    gameclient->Ready(gameclient);

    SDL_RenderClear(scene->window->renderer_window);
}

void GameScene_UpdatePlayerInfo(TScene *scene, player_t player)
{
    unsigned int block_start_x;
    unsigned int block_start_y;
    char *res_id = malloc(sizeof(char) * 255);
    char *info_line = malloc(sizeof(char) * 1024);
    TText *txt_name = NULL;
    TText *txt_info = NULL;
    TSprite *sp_game_over = NULL;

    switch (player.p_id) {
        case 0:
            block_start_x = 0;
            block_start_y = 0;
            break;
        case 1:
            block_start_x = WIN_WIDTH - BLOCK_INFO_WIDTH;
            block_start_y = 0;
            break;
        case 2:
            block_start_x = 0;
            block_start_y = WIN_HEIGHT - BLOCK_INFO_HEIGHT;
            break;
        case 3:
            block_start_x = WIN_WIDTH - BLOCK_INFO_WIDTH;
            block_start_y = WIN_HEIGHT - BLOCK_INFO_HEIGHT;
            break;
        default:
            free(res_id);
            free(info_line);
            return;
    }

    sprintf(res_id, "PLAYER_%u_NAME", player.p_id);
    txt_name = (TText*)scene->Get_Drawable(scene, res_id);
    sprintf(res_id, "PLAYER_%u_INFOS", player.p_id);
    txt_info = (TText*)scene->Get_Drawable(scene, res_id);
    sprintf(res_id, "PLAYER_%u_GO", player.p_id);
    sp_game_over = (TSprite*)scene->Get_Drawable(scene, res_id);

    // Création du block d'info si non existant
    if (!txt_name) {
        SDL_Rect pos_text = {0, 0, 0, 0};
        SDL_Color color = {255, 255, 255, 255};
        TTF_Font *font = loadFont(FONT_PATH "fixedsys.ttf", 14);

        txt_name = New_TText(scene, "[PLAYER_NAME]", font, color, pos_text);
        sprintf(res_id, "PLAYER_%u_NAME", player.p_id);
        scene->Add_Drawable(scene, (TDrawable*)txt_name,
            res_id, 2, GLIB_FREE_ON_UNLOAD
        );
        font = loadFont(FONT_PATH "fixedsys.ttf", 14);
        txt_info = New_TText(scene, "[PLAYER_INFOS]", font, color, pos_text);
        sprintf(res_id, "PLAYER_%u_INFOS", player.p_id);
        scene->Add_Drawable(scene, (TDrawable*)txt_info,
            res_id, 2, GLIB_FREE_ON_UNLOAD
        );

    }
    txt_name->Change_Text(txt_name, scene, player.username);
    txt_name->pos.x = block_start_x + (BLOCK_INFO_WIDTH / 2) - (txt_name->pos.w / 2);
    txt_name->pos.y = block_start_y + 20;

    sprintf(info_line, "Life: %02u/%02d | Bombs left: %02u/%02u",
        player.specs.life, PLAYER_MAX_LIFE,
        player.specs.bombs_left, player.specs.bombs_capacity
    );
    txt_info->Change_Text(txt_info, scene, info_line);
    txt_info->pos.x = block_start_x + (BLOCK_INFO_WIDTH / 2) - (txt_info->pos.w / 2);
    txt_info->pos.y = (txt_name->pos.y + txt_name->pos.h) + 20;

    sprintf(res_id, "PLAYER_%u_HPBAR", player.p_id);
    TSprite *hbar = (TSprite*)scene->Get_Drawable(scene, res_id);
    hbar->pos.w = (int)(32 * ((float)player.specs.life / 100.0));

    if (player.specs.life == 0 && sp_game_over == NULL) {
        SDL_Rect pos = {block_start_x, block_start_y, BLOCK_INFO_WIDTH, BLOCK_INFO_HEIGHT};

        sp_game_over = New_TSprite(scene, CHAR_PATH "game_over.png", pos);
        sprintf(res_id, "PLAYER_%u_GO", player.p_id);
        scene->Add_Drawable(scene, (TDrawable*)sp_game_over,
            res_id, 1, GLIB_FREE_ON_UNLOAD
        );

        sprintf(res_id, "PLAYER_%u_%u", player.p_id, player.direction);
        TAnimatedSprites *asp = (TAnimatedSprites*)scene->Get_Drawable(scene, res_id);
        asp->is_visible = 0;

        sprintf(res_id, "PLAYER_%u_HPBAR", player.p_id);
        ((TSprite*)scene->Get_Drawable(scene, res_id))->is_visible = 0;
        sprintf(res_id, "PLAYER_%u_HPBG", player.p_id);
        ((TSprite*)scene->Get_Drawable(scene, res_id))->is_visible = 0;
    }

    free(res_id);
    free(info_line);
}

static void On_Event(TScene* scene, SDL_Event event)
{
    if (!scene) return;
    if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_ESCAPE)
            gameclient->Leave_Game(gameclient, 1);
        if (event.key.keysym.sym == SDLK_SPACE) {
            gameclient->Place_Bomb(gameclient);
        }
    }
}

static void On_Tick(TScene* scene)
{
    const Uint8 *keyboard = SDL_GetKeyboardState(NULL);

    if (keyboard[SDL_SCANCODE_LEFT]) {
        gameclient->Move(gameclient, WEST);
    } else if (keyboard[SDL_SCANCODE_RIGHT]) {
        gameclient->Move(gameclient, EAST);
    } else if (keyboard[SDL_SCANCODE_UP]) {
        gameclient->Move(gameclient, NORTH);
    } else if (keyboard[SDL_SCANCODE_DOWN]) {
        gameclient->Move(gameclient, SOUTH);
    }

    SDL_RenderClear(scene->window->renderer_window);
    gameclient->Handle_Messages(gameclient);
    scene->Draw_Drawables(scene);
    SDL_RenderPresent(scene->window->renderer_window);
    if (scene->window->finished)
        gameclient->Leave_Game(gameclient, 1);
}

static void On_Unload(TScene* scene)
{
    if (IS_DEBUG)
        printf("Scene [%s]: On_Unload method called\n", scene->scene_id);
    scene->Pause_BackgroundMusic(scene, 1);
}

static void On_Finish(TScene* scene)
{
    if (IS_DEBUG)
        printf("Scene [%s]: Finish method called\n", scene->scene_id);
    gameclient->Free(gameclient);
}

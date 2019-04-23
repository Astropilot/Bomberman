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
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "glib.h"
#include "logic/client.h"
#include "core/extra.h"
#include "core/player.h"
#include "core/minion.h"
#include "core/utils.h"
#include "ui/scene_game.h"
#include "network/game/client.h"
#include "network/network.h"
#include "network/game/server.h"
#include "network/packets/packet.h"
#include "network/packets/packet_ack_gameinit.h"
#include "network/packets/packet_ack_move.h"
#include "network/packets/packet_ack_placebomb.h"
#include "network/packets/packet_ack_bombexplode.h"
#include "network/packets/packet_ack_playerupdate.h"
#include "network/packets/packet_ack_minionupdate.h"
#include "network/packets/packet_ack_endgame.h"
#include "network/packets/packet_disconnect.h"

static void handle_disconnect(TGameClient *game, TMessage message);
static void handle_gameinit(TGameClient *game, TMessage message);
static void handle_move(TGameClient *game, TMessage message);
static void handle_placebomb(TGameClient *game, TMessage message);
static void handle_bombexplode(TGameClient *game, TMessage message);
static void handle_playerupdate(TGameClient *game, TMessage message);
static void handle_minionupdate(TGameClient *game, TMessage message);
static void handle_endgame(TGameClient *game, TMessage message);

static void (*message_handler[])(TGameClient*, TMessage) = {
    [ACK_DISCONNECT] = handle_disconnect,
    [ACK_GAME_INIT] = handle_gameinit,
    [ACK_MOVE] = handle_move,
    [ACK_PLACE_BOMB] = handle_placebomb,
    [ACK_BOMB_EXPLODE] = handle_bombexplode,
    [ACK_PLAYER_UPDATE] = handle_playerupdate,
    [ACK_END_GAME] = handle_endgame,
    [ACK_MINION_UPDATE] = handle_minionupdate
};

void handle_game_logic(TGameClient *game, TMessage message, int packet_id)
{
    if (!game) return;

    (*message_handler[packet_id])(game, message);
}

static void handle_disconnect(TGameClient *game, TMessage message)
{
    free(message.message);
    game->Leave_Game(game);
}

static void handle_gameinit(TGameClient *game, TMessage message)
{
    TAckGameInitPacket *p_as = New_TAckGameInitPacket(message.message);
    p_as->Unserialize(p_as);

    unsigned int i;
    unsigned int j;
    char *id = malloc(sizeof(char) * 255);
    for (i = 0; i < p_as->nb_players; i++) {
        player_t player = p_as->players[i];

        sprintf(id, "PLAYER_%u_HPBG", i);
        TSprite *hbg = (TSprite*)game->game_scene->Get_Drawable(game->game_scene, id);
        hbg->pos.x  = player.pos.x;
        hbg->pos.y  = player.pos.y - 10;
        sprintf(id, "PLAYER_%u_HPBAR", i);
        TSprite *hbar = (TSprite*)game->game_scene->Get_Drawable(game->game_scene, id);
        hbar->pos.x  = player.pos.x;
        hbar->pos.y  = player.pos.y - 10;

        sprintf(id, "PLAYER_%u_%u", i, SOUTH);
        ((TAnimatedSprites*)game->game_scene->Get_Drawable(game->game_scene, id))->is_visible = 0;
        sprintf(id, "PLAYER_%u_%u", i, NORTH);
        ((TAnimatedSprites*)game->game_scene->Get_Drawable(game->game_scene, id))->is_visible = 0;
        sprintf(id, "PLAYER_%u_%u", i, WEST);
        ((TAnimatedSprites*)game->game_scene->Get_Drawable(game->game_scene, id))->is_visible = 0;
        sprintf(id, "PLAYER_%u_%u", i, EAST);
        ((TAnimatedSprites*)game->game_scene->Get_Drawable(game->game_scene, id))->is_visible = 0;

        sprintf(id, "PLAYER_%u_%u", i, player.direction);
        TAnimatedSprites *asp = (TAnimatedSprites*)game->game_scene->Get_Drawable(game->game_scene, id);
        asp->pos.x = player.pos.x;
        asp->pos.y = player.pos.y;
        asp->is_visible = 1;
        GameScene_UpdatePlayerInfo(game->game_scene, player);
    }

    TAnimatedSprites *sp_minion =
        (TAnimatedSprites*)game->game_scene->Get_Drawable(game->game_scene, "MINION");
    map_to_pix(
        (int)p_as->minion.pos.x, (int)p_as->minion.pos.y,
        (int*)&(i), (int*)&(j)
    );
    sp_minion->is_visible = 1;
    sp_minion->pos.x = i;
    sp_minion->pos.y = j;

    for (i = 0; i < MAP_HEIGHT; i++) {
        for (j = 0; j < MAP_WIDTH; j++) {
            switch (p_as->block_map[i][j]) {
                case WALL:;
                    SDL_Rect posw = {0, 0, 32, 32};

                    TSprite *spw = New_TSprite(game->game_scene, MAP_PATH "wall.png", posw);

                    map_to_pix(j, i, &(spw->pos.x), &(spw->pos.y));
                    sprintf(id, "WALL_%u_%u", i, j);
                    game->game_scene->Add_Drawable(game->game_scene,
                        (TDrawable*)spw, id, 3, GLIB_FREE_ON_UNLOAD
                    );
                    break;
                case BREAKABLE_WALL:;
                    SDL_Rect posbw = {0, 0, 32, 32};
                    TSprite *spbw = New_TSprite(game->game_scene,
                        MAP_PATH "breakable_wall.png", posbw
                    );

                    map_to_pix(j, i, &(spbw->pos.x), &(spbw->pos.y));
                    sprintf(id, "BWALL_%u_%u", i, j);
                    game->game_scene->Add_Drawable(game->game_scene,
                        (TDrawable*)spbw, id, 3, GLIB_FREE_ON_UNLOAD
                    );
                default:
                    break;
            }
        }
    }
    free(id);
    p_as->Free(p_as);
}

static void handle_move(TGameClient *game, TMessage message)
{
    TAckMovePacket *p_mv = New_TAckMovePacket(message.message);
    p_mv->Unserialize(p_mv);

    char *id = malloc(sizeof(char) * 255);
    player_t player = p_mv->player;

    sprintf(id, "PLAYER_%u_%u", p_mv->player_id, SOUTH);
    ((TAnimatedSprites*)game->game_scene->Get_Drawable(game->game_scene, id))->is_visible = 0;
    sprintf(id, "PLAYER_%u_%u", p_mv->player_id, NORTH);
    ((TAnimatedSprites*)game->game_scene->Get_Drawable(game->game_scene, id))->is_visible = 0;
    sprintf(id, "PLAYER_%u_%u", p_mv->player_id, WEST);
    ((TAnimatedSprites*)game->game_scene->Get_Drawable(game->game_scene, id))->is_visible = 0;
    sprintf(id, "PLAYER_%u_%u", p_mv->player_id, EAST);
    ((TAnimatedSprites*)game->game_scene->Get_Drawable(game->game_scene, id))->is_visible = 0;

    sprintf(id, "PLAYER_%u_%u", p_mv->player_id, player.direction);
    TAnimatedSprites *asp = (TAnimatedSprites*)game->game_scene->Get_Drawable(game->game_scene, id);
    asp->pos.x = player.pos.x;
    asp->pos.y = player.pos.y;
    asp->is_visible = 1;

    sprintf(id, "PLAYER_%u_HPBG", p_mv->player_id);
    TSprite *hbg = (TSprite*)game->game_scene->Get_Drawable(game->game_scene, id);
    hbg->pos.x = player.pos.x;
    hbg->pos.y = player.pos.y - 10;
    sprintf(id, "PLAYER_%u_HPBAR", p_mv->player_id);
    TSprite *hbar = (TSprite*)game->game_scene->Get_Drawable(game->game_scene, id);
    hbar->pos.x = player.pos.x;
    hbar->pos.y = player.pos.y - 10;

    if (p_mv->take_extra) {
        int x_tmp, y_tmp;
        TSound *power_up = (TSound*)game->game_scene->Get_Drawable(
            game->game_scene, "POWER_UP"
        );

        pix_to_map((int)player.pos.x, (int)player.pos.y, &x_tmp, &y_tmp);
        sprintf(id, "EXTRA_%d_%d", y_tmp, x_tmp);
        game->game_scene->Free_Drawable(game->game_scene, id);
        power_up->Play(power_up, 1);
    }

    free(id);
    p_mv->Free(p_mv);
}

static void handle_placebomb(TGameClient *game, TMessage message)
{
    TAckPlaceBombPacket *p_ab = New_TAckPlaceBombPacket(message.message);
    p_ab->Unserialize(p_ab);

    if (p_ab->status == BOMB_POSED) {
        SDL_Rect size_bomb = {0, 0, 48, 48};
        SDL_Rect pos_bomb = {p_ab->x + 8, p_ab->y + 8, 16, 16};
        char *bomb_id = malloc(sizeof(char) * 255);
        TAnimatedSprites *sp = New_TAnimatedSprites(
            game->game_scene, BOMB_PATH "static_bomb_%02d.png", 3,
            size_bomb, pos_bomb, 100, -1
        );
        TSound *bomb_pose = (TSound*)game->game_scene->Get_Drawable(game->game_scene, "BOMB_POSE");

        sprintf(bomb_id, "BOMB_%u", p_ab->bomb_id);
        game->game_scene->Add_Drawable(game->game_scene, (TDrawable*)sp, bomb_id, 2, GLIB_FREE_ON_UNLOAD);
        free(bomb_id);
        game->bomb_offset = p_ab->bomb_id;
        bomb_pose->Play(bomb_pose, 1);
    }

    p_ab->Free(p_ab);
}

static void handle_bombexplode(TGameClient *game, TMessage message)
{
    TAckBombExplodePacket *p_b = New_TAckBombExplodePacket(message.message);
    p_b->Unserialize(p_b);

    unsigned int i;
    char *id = malloc(sizeof(char) * 255);
    sprintf(id, "BOMB_%u", p_b->bomb.id);
    game->game_scene->Free_Drawable(game->game_scene, id);

    SDL_Rect size_bomb = {0, 0, 94, 94};
    SDL_Rect pos_bomb = {0, 0, 32, 32};
    map_to_pix((int)p_b->bomb.bomb_pos.x, (int)p_b->bomb.bomb_pos.y, &pos_bomb.x, &pos_bomb.y);
    TAnimatedSprites *sp = New_TAnimatedSprites(
        game->game_scene, BOMB_PATH "bomb_explode_%02d.png", 5,
        size_bomb, pos_bomb, 128, 1
    );
    game->game_scene->Add_Drawable(
        game->game_scene, (TDrawable*)sp, "BOMB",
        2, GLIB_FREE_ON_UNLOAD
    );

    for (i = 0; i < p_b->destroyed_count; i++) {
        if (p_b->destroyed_blocks[i].type == BREAKABLE_WALL) {
            sprintf(id, "BWALL_%u_%u", p_b->destroyed_blocks[i].pos.y, p_b->destroyed_blocks[i].pos.x);
            game->game_scene->Free_Drawable(game->game_scene, id);
        } else {
            sprintf(id, "EXTRA_%u_%u", p_b->destroyed_blocks[i].pos.y, p_b->destroyed_blocks[i].pos.x);
            game->game_scene->Free_Drawable(game->game_scene, id);
        }
    }
    for (i = 0; i < p_b->flames_count; i++) {
        SDL_Rect size_flame = {0, 0, 48, 48};
        SDL_Rect pos_flame = {0, 0, 32, 32};

        map_to_pix((int)p_b->flames_blocks[i].x, (int)p_b->flames_blocks[i].y, &pos_flame.x, &pos_flame.y);
        TAnimatedSprites *sp_flame = New_TAnimatedSprites(
            game->game_scene, BOMB_PATH "flame_%02d.png", 5,
            size_flame, pos_flame, 128, 1
        );
        game->game_scene->Add_Drawable(
            game->game_scene, (TDrawable*)sp_flame, "FLAME",
            3, GLIB_FREE_ON_UNLOAD
        );
    }
    for (i = 0; i < p_b->extra_count; i++) {
        SDL_Rect size_extra = {0, 0, 64, 64};
        SDL_Rect pos_extra = {0, 0, 32, 32};

        map_to_pix((int)p_b->extra_blocks[i].pos.x, (int)p_b->extra_blocks[i].pos.y, &pos_extra.x, &pos_extra.y);
        sprintf(id, "EXTRA_%u_%u", p_b->extra_blocks[i].pos.y, p_b->extra_blocks[i].pos.x);
        TAnimatedSprites *sp_extra = New_TAnimatedSprites(
            game->game_scene, extra_to_resource(p_b->extra_blocks[i].type), 7,
            size_extra, pos_extra, 128, -1
        );
        game->game_scene->Add_Drawable(
            game->game_scene, (TDrawable*)sp_extra, id,
            3, GLIB_FREE_ON_UNLOAD
        );
    }

    TSound *bomb_explode = (TSound*)game->game_scene->Get_Drawable(
        game->game_scene, "BOMB_EXPLODE"
    );

    bomb_explode->Play(bomb_explode, 1);

    free(id);
    p_b->Free(p_b);
}

static void handle_playerupdate(TGameClient *game, TMessage message)
{
    TAckPlayerUpdatePacket *p_pu = New_TAckPlayerUpdatePacket(message.message);
    p_pu->Unserialize(p_pu);

    GameScene_UpdatePlayerInfo(game->game_scene, p_pu->player);

    p_pu->Free(p_pu);
}

static void handle_minionupdate(TGameClient *game, TMessage message)
{
    TAckMinionUpdatePacket *p_mu = New_TAckMinionUpdatePacket(message.message);
    TAnimatedSprites *sp_minion = (TAnimatedSprites*)game->game_scene->Get_Drawable(game->game_scene, "MINION");
    unsigned int x_pix;
    unsigned int y_pix;

    p_mu->Unserialize(p_mu);

    map_to_pix(
        (int)p_mu->minion_pos.x, (int)p_mu->minion_pos.y,
        (int*)&(x_pix), (int*)&(y_pix)
    );
    sp_minion->is_visible = 1;
    sp_minion->pos.x = x_pix;
    sp_minion->pos.y = y_pix;

    p_mu->Free(p_mu);
}

static void handle_endgame(TGameClient *game, TMessage message)
{
    TAckEndGamePacket *p_eg = New_TAckEndGamePacket(message.message);
    p_eg->Unserialize(p_eg);

    TReqDisconnectPacket *p_d = New_TReqDisconnectPacket(NULL);
    p_d->reason = (game->is_owner ? MASTER_LEAVE : USER_QUIT);
    p_d->player = (unsigned int)game->player;
    game->client->Send(game->client, packet_to_message((TPacket*)p_d, 1));
    game->client->Disconnect(game->client);
    game->client->Free(game->client);
    game->client = NULL;
    game->is_owner = 0;
    game->player = -1;
    if (game->gameserver) {
        game->gameserver->Stop(game->gameserver);
        game->gameserver->Free(game->gameserver);
        game->gameserver = NULL;
    }
    game_result_t game_result = (game_result_t)p_eg->game_result;
    player_t *player_winner = p_eg->winner;
    p_eg->winner = NULL;
    p_eg->Free(p_eg);
    game->game_scene->window->Show_Scene(
        game->game_scene->window, "SCENE_END_GAME", 2,
        game_result, player_winner
    );
}

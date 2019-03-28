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

#include <string.h>
#include <stdio.h>

#include "network/game/client.h"
#include "glib.h"
#include "core/player.h"
#include "ui/frame_game.h"
#include "network/network.h"
#include "network/game/server.h"
#include "network/packets/packet.h"
#include "network/packets/packet_req_move.h"
#include "network/packets/packet_req_placebomb.h"
#include "network/packets/packet_req_ready.h"
#include "network/packets/packet_ack_gameinit.h"
#include "network/packets/packet_ack_move.h"
#include "network/packets/packet_ack_placebomb.h"
#include "network/packets/packet_ack_bombexplode.h"
#include "network/packets/packet_ack_playerupdate.h"
#include "network/packets/packet_ack_endgame.h"
#include "network/packets/packet_disconnect.h"
#include "core/utils.h"
#include "main.h"

TGameClient* New_TGameClient()
{
    TGameClient *this = malloc(sizeof(TGameClient));

    if(!this) return NULL;

    this->client = NULL;
    this->gameserver = NULL;
    this->game_frame = NULL;
    this->is_owner = 0;
    this->player = -1;
    this->Register_Frame = TGameClient_Register_Frame;
    this->Ready = TGameClient_Ready;
    this->Move = TGameClient_Move;
    this->Place_Bomb = TGameClient_Place_Bomb;
    this->Handle_Messages = TGameClient_Handle_Messages;
    this->Leave_Game = TGameClient_Leave_Game;
    this->Free = TGameClient_New_Free;
    return this;
}

TFrame *TGameClient_Register_Frame(TGameClient *this, TFrame *frame)
{
    this->game_frame = frame;
    return (frame);
}

void TGameClient_Ready(TGameClient *this)
{
    TReqReadyPacket *p_rr = New_TReqReadyPacket(NULL);

    p_rr->player = this->player;
    this->client->Send(this->client, packet_to_message((TPacket*)p_rr, 1));
}

void TGameClient_Move(TGameClient *this, direction_t direction)
{
    TReqMovePlayerPacket *p_rm = New_TReqMovePlayerPacket(NULL);

    p_rm->dir = (unsigned int)direction;
    p_rm->player = this->player;
    this->client->Send(this->client, packet_to_message((TPacket*)p_rm, 1));
}

void TGameClient_Place_Bomb(TGameClient *this)
{
    TReqPlaceBombPacket *p_rb = New_TReqPlaceBombPacket(NULL);

    p_rb->player = this->player;
    this->client->Send(this->client, packet_to_message((TPacket*)p_rb, 1));
}

void TGameClient_Handle_Messages(TGameClient *this)
{
    if (!this->client)
        return;

    TMessage message;
    int packet_id;
    int res_read = this->client->Recv(this->client, &message);
    #ifdef _WIN32
        if (res_read == WSAEWOULDBLOCK || res_read == EAGAIN || message.len <= 0) return;
    #else
        if (res_read == EWOULDBLOCK || res_read == EAGAIN || message.len <= 0) return;
    #endif

    packet_id = extract_packet_id(message.message);
    switch (packet_id) {
        case ACK_DISCONNECT:;
            free(message.message);
            this->Leave_Game(this);
            break;
        case ACK_GAME_INIT:;
            TAckGameInitPacket *p_as = New_TAckGameInitPacket(message.message);
            p_as->Unserialize(p_as);

            unsigned int i;
            unsigned int j;
            char *id = malloc(sizeof(char) * 255);
            for (i = 0; i < p_as->nb_players; i++) {
                player_t player = p_as->players[i];

                sprintf(id, "PLAYER_%u_HPBG", i);
                TSprite *hbg = (TSprite*)this->game_frame->Get_Drawable(this->game_frame, id);
                hbg->pos.x  = player.pos.x;
                hbg->pos.y  = player.pos.y - 10;
                sprintf(id, "PLAYER_%u_HPBAR", i);
                TSprite *hbar = (TSprite*)this->game_frame->Get_Drawable(this->game_frame, id);
                hbar->pos.x  = player.pos.x;
                hbar->pos.y  = player.pos.y - 10;

                sprintf(id, "PLAYER_%u_%u", i, SOUTH);
                ((TAnimatedSprites*)this->game_frame->Get_Drawable(this->game_frame, id))->is_visible = 0;
                sprintf(id, "PLAYER_%u_%u", i, NORTH);
                ((TAnimatedSprites*)this->game_frame->Get_Drawable(this->game_frame, id))->is_visible = 0;
                sprintf(id, "PLAYER_%u_%u", i, WEST);
                ((TAnimatedSprites*)this->game_frame->Get_Drawable(this->game_frame, id))->is_visible = 0;
                sprintf(id, "PLAYER_%u_%u", i, EAST);
                ((TAnimatedSprites*)this->game_frame->Get_Drawable(this->game_frame, id))->is_visible = 0;

                sprintf(id, "PLAYER_%u_%u", i, player.direction);
                TAnimatedSprites *asp = (TAnimatedSprites*)this->game_frame->Get_Drawable(this->game_frame, id);
                asp->pos.x = player.pos.x;
                asp->pos.y = player.pos.y;
                asp->is_visible = 1;
                GameFrame_UpdatePlayerInfo(this->game_frame, player);
            }


            for (i = 0; i < MAP_HEIGHT; i++) {
                for (j = 0; j < MAP_WIDTH; j++) {
                    switch (p_as->block_map[i][j]) {
                        case WALL:;
                            SDL_Rect posw = {0, 0, 32, 32};

                            TSprite *spw = New_TSprite(this->game_frame, MAP_PATH "wall.png", posw);

                            map_to_pix(j, i, &(spw->pos.x), &(spw->pos.y));
                            sprintf(id, "WALL_%u_%u", i, j);
                            this->game_frame->Add_Drawable(this->game_frame, (TDrawable*)spw, id, 3);
                            break;
                        case BREAKABLE_WALL:;
                        SDL_Rect posbw = {0, 0, 32, 32};
                        TSprite *spbw = New_TSprite(this->game_frame, MAP_PATH "breakable_wall.png", posbw);

                        map_to_pix(j, i, &(spbw->pos.x), &(spbw->pos.y));
                        sprintf(id, "BWALL_%u_%u", i, j);
                        this->game_frame->Add_Drawable(this->game_frame, (TDrawable*)spbw, id, 3);
                        default:
                            break;
                    }
                }
            }
            free(id);

            p_as->Free(p_as);
            break;
        case ACK_MOVE:;
            TAckMovePacket *p_mv = New_TAckMovePacket(message.message);
            p_mv->Unserialize(p_mv);

            id = malloc(sizeof(char) * 255);
            player_t player = p_mv->player;

            sprintf(id, "PLAYER_%u_%u", p_mv->player_id, SOUTH);
            ((TAnimatedSprites*)this->game_frame->Get_Drawable(this->game_frame, id))->is_visible = 0;
            sprintf(id, "PLAYER_%u_%u", p_mv->player_id, NORTH);
            ((TAnimatedSprites*)this->game_frame->Get_Drawable(this->game_frame, id))->is_visible = 0;
            sprintf(id, "PLAYER_%u_%u", p_mv->player_id, WEST);
            ((TAnimatedSprites*)this->game_frame->Get_Drawable(this->game_frame, id))->is_visible = 0;
            sprintf(id, "PLAYER_%u_%u", p_mv->player_id, EAST);
            ((TAnimatedSprites*)this->game_frame->Get_Drawable(this->game_frame, id))->is_visible = 0;

            sprintf(id, "PLAYER_%u_%u", p_mv->player_id, player.direction);
            TAnimatedSprites *asp = (TAnimatedSprites*)this->game_frame->Get_Drawable(this->game_frame, id);
            asp->pos.x = player.pos.x;
            asp->pos.y = player.pos.y;
            asp->is_visible = 1;

            sprintf(id, "PLAYER_%u_HPBG", p_mv->player_id);
            TSprite *hbg = (TSprite*)this->game_frame->Get_Drawable(this->game_frame, id);
            hbg->pos.x = player.pos.x;
            hbg->pos.y = player.pos.y - 10;
            sprintf(id, "PLAYER_%u_HPBAR", p_mv->player_id);
            TSprite *hbar = (TSprite*)this->game_frame->Get_Drawable(this->game_frame, id);
            hbar->pos.x = player.pos.x;
            hbar->pos.y = player.pos.y - 10;

            if (p_mv->take_extra) {
                int x_tmp, y_tmp;
                pix_to_map((int)player.pos.x, (int)player.pos.y, &x_tmp, &y_tmp);
                sprintf(id, "EXTRA_%d_%d", y_tmp, x_tmp);
                this->game_frame->Free_Drawable(this->game_frame, id);
            }

            free(id);
            p_mv->Free(p_mv);
            break;
        case ACK_PLACE_BOMB:;
            TAckPlaceBombPacket *p_ab = New_TAckPlaceBombPacket(message.message);
            p_ab->Unserialize(p_ab);

            if (p_ab->status == BOMB_POSED) {
                SDL_Rect size_bomb = {0, 0, 48, 48};
                SDL_Rect pos_bomb = {p_ab->x + 8, p_ab->y + 8, 16, 16};
                char *bomb_id = malloc(sizeof(char) * 255);
                TAnimatedSprites *sp = New_TAnimatedSprites(
                    this->game_frame, BOMB_PATH "static_bomb_%02d.png", 3,
                    size_bomb, pos_bomb, 100, -1
                );
                sprintf(bomb_id, "BOMB_%u", p_ab->bomb_id);
                this->game_frame->Add_Drawable(this->game_frame, (TDrawable*)sp, bomb_id, 2);
                free(bomb_id);
                this->bomb_offset = p_ab->bomb_id;
            }

            p_ab->Free(p_ab);
            break;
        case ACK_BOMB_EXPLODE:;
            TAckBombExplodePacket *p_b = New_TAckBombExplodePacket(message.message);
            p_b->Unserialize(p_b);

            id = malloc(sizeof(char) * 255);
            sprintf(id, "BOMB_%u", p_b->bomb.id);
            this->game_frame->Free_Drawable(this->game_frame, id);

            SDL_Rect size_bomb = {0, 0, 94, 94};
            SDL_Rect pos_bomb = {0, 0, 32, 32};
            map_to_pix((int)p_b->bomb.bomb_pos.x, (int)p_b->bomb.bomb_pos.y, &pos_bomb.x, &pos_bomb.y);
            TAnimatedSprites *sp = New_TAnimatedSprites(
                this->game_frame, BOMB_PATH "bomb_explode_%02d.png", 5,
                size_bomb, pos_bomb, 128, 1
            );
            this->game_frame->Add_Drawable(this->game_frame, (TDrawable*)sp, "BOMB", 2);

            for (i = 0; i < p_b->destroyed_count; i++) {
                sprintf(id, "BWALL_%u_%u", p_b->destroyed_walls[i].y, p_b->destroyed_walls[i].x);
                this->game_frame->Free_Drawable(this->game_frame, id);
            }
            for (i = 0; i < p_b->flames_count; i++) {
                SDL_Rect size_flame = {0, 0, 48, 48};
                SDL_Rect pos_flame = {0, 0, 32, 32};

                map_to_pix((int)p_b->flames_blocks[i].x, (int)p_b->flames_blocks[i].y, &pos_flame.x, &pos_flame.y);
                TAnimatedSprites *sp_flame = New_TAnimatedSprites(
                    this->game_frame, BOMB_PATH "flame_%02d.png", 5,
                    size_flame, pos_flame, 128, 2
                );
                this->game_frame->Add_Drawable(this->game_frame, (TDrawable*)sp_flame, "FLAME", 3);
            }
            for (i = 0; i < p_b->extra_count; i++) {
                SDL_Rect size_extra = {0, 0, 64, 64};
                SDL_Rect pos_extra = {0, 0, 32, 32};

                map_to_pix((int)p_b->extra_blocks[i].pos.x, (int)p_b->extra_blocks[i].pos.y, &pos_extra.x, &pos_extra.y);
                sprintf(id, "EXTRA_%u_%u", p_b->extra_blocks[i].pos.y, p_b->extra_blocks[i].pos.x);
                TAnimatedSprites *sp_extra = New_TAnimatedSprites(
                    this->game_frame, extra_to_resource(p_b->extra_blocks[i].type), 7,
                    size_extra, pos_extra, 128, -1
                );
                this->game_frame->Add_Drawable(this->game_frame, (TDrawable*)sp_extra, id, 3);
            }
            free(id);
            p_b->Free(p_b);
            break;
        case ACK_PLAYER_UPDATE:;
            TAckPlayerUpdatePacket *p_pu = New_TAckPlayerUpdatePacket(message.message);
            p_pu->Unserialize(p_pu);

            GameFrame_UpdatePlayerInfo(this->game_frame, p_pu->player);

            p_pu->Free(p_pu);
            break;
        case ACK_END_GAME:;
            TAckEndGamePacket *p_eg = New_TAckEndGamePacket(message.message);
            p_eg->Unserialize(p_eg);

            TReqDisconnectPacket *p_d = New_TReqDisconnectPacket(NULL);
            p_d->reason = (this->is_owner ? MASTER_LEAVE : USER_QUIT);
            p_d->player = (unsigned int)this->player;
            this->client->Send(this->client, packet_to_message((TPacket*)p_d, 1));
            this->client->Disconnect(this->client);
            this->client->Free(this->client);
            this->client = NULL;
            this->is_owner = 0;
            this->player = -1;
            if (this->gameserver) {
                this->gameserver->Stop(this->gameserver);
                this->gameserver->Free(this->gameserver);
                this->gameserver = NULL;
            }
            game_result_t game_result = (game_result_t)p_eg->game_result;
            player_t *player_winner = p_eg->winner;
            p_eg->winner = NULL;
            p_eg->Free(p_eg);
            this->game_frame->window->Show_Frame(
                this->game_frame->window, "FRAME_END_GAME", 2,
                game_result, player_winner
            );
            break;
        default:
            free(message.message);
    }
}

void TGameClient_Leave_Game(TGameClient *this)
{
    if (!(this->client))
        return;

    TReqDisconnectPacket *p_d = New_TReqDisconnectPacket(NULL);
    p_d->reason = (this->is_owner ? MASTER_LEAVE : USER_QUIT);
    p_d->player = (unsigned int)this->player;
    this->client->Send(this->client, packet_to_message((TPacket*)p_d, 1));
    this->client->Disconnect(this->client);
    this->client->Free(this->client);
    this->client = NULL;
    this->is_owner = 0;
    this->player = -1;
    if (this->gameserver) {
        this->gameserver->Stop(this->gameserver);
        this->gameserver->Free(this->gameserver);
        this->gameserver = NULL;
    }
    this->game_frame->window->Show_Frame(this->game_frame->window, "FRAME_MAIN_MENU", 0);
}

void TGameClient_New_Free(TGameClient *this)
{
    free(this);
}

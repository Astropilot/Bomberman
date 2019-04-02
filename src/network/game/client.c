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

#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "glib.h"
#include "network/game/client.h"
#include "logic/client.h"
#include "core/extra.h"
#include "core/player.h"
#include "ui/frame_game.h"
#include "network/network.h"
#include "network/game/server.h"
#include "network/packets/packet.h"
#include "network/packets/packet_req_move.h"
#include "network/packets/packet_req_placebomb.h"
#include "network/packets/packet_req_ready.h"
#include "network/packets/packet_disconnect.h"
#include "core/utils.h"

TGameClient* New_TGameClient()
{
    TGameClient *this = malloc(sizeof(TGameClient));

    if(!this) return (NULL);

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
    return (this);
}

TFrame *TGameClient_Register_Frame(TGameClient *this, TFrame *frame)
{
    this->game_frame = frame;
    return (frame);
}

void TGameClient_Ready(TGameClient *this)
{
    TReqReadyPacket *p_rr = New_TReqReadyPacket(NULL);

    if (this && p_rr) {
        p_rr->player = this->player;
        this->client->Send(this->client, packet_to_message((TPacket*)p_rr, 1));
    } else
        if (p_rr) p_rr->Free(p_rr);
}

void TGameClient_Move(TGameClient *this, direction_t direction)
{
    TReqMovePlayerPacket *p_rm = New_TReqMovePlayerPacket(NULL);

    if (this && p_rm) {
        p_rm->dir = (unsigned int)direction;
        p_rm->player = this->player;
        this->client->Send(this->client, packet_to_message((TPacket*)p_rm, 1));
    } else
        if (p_rm) p_rm->Free(p_rm);
}

void TGameClient_Place_Bomb(TGameClient *this)
{
    TReqPlaceBombPacket *p_rb = New_TReqPlaceBombPacket(NULL);

    if (this && p_rb) {
        p_rb->player = this->player;
        this->client->Send(this->client, packet_to_message((TPacket*)p_rb, 1));
    } else
        if (p_rb) p_rb->Free(p_rb);
}

void TGameClient_Handle_Messages(TGameClient *this)
{
    if (!this || !this->client) return;

    TMessage message;
    int packet_id;
    int res_read = this->client->Recv(this->client, &message);
    #ifdef _WIN32
        if (res_read == WSAEWOULDBLOCK || res_read == EAGAIN || message.len <= 0)
            return;
    #else
        if (res_read == EWOULDBLOCK || res_read == EAGAIN || message.len <= 0)
            return;
    #endif

    packet_id = extract_packet_id(message.message);
    handle_game_logic(this, message, packet_id);
}

void TGameClient_Leave_Game(TGameClient *this)
{
    if (!this || !this->client) return;

    TReqDisconnectPacket *p_d = New_TReqDisconnectPacket(NULL);

    if (p_d) {
        p_d->reason = (this->is_owner ? MASTER_LEAVE : USER_QUIT);
        p_d->player = (unsigned int)this->player;
        this->client->Send(this->client, packet_to_message((TPacket*)p_d, 1));
    }
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

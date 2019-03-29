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

#include "network/packets/packet.h"
#include "network/packets/packet_req_move.h"
#include "network/network.h"

TReqMovePlayerPacket *New_TReqMovePlayerPacket(unsigned char *raw)
{
    TReqMovePlayerPacket *this = malloc(sizeof(TReqMovePlayerPacket));

    if(!this) return (NULL);

    this->raw_packet = raw;
    this->packet_id = REQ_MOVE;
    this->Serialize = TReqMovePlayerPacket_Serialize;
    this->Unserialize = TReqMovePlayerPacket_Unserialize;
    this->Free = TReqMovePlayerPacket_New_Free;
    return (this);
}

int TReqMovePlayerPacket_Serialize(TReqMovePlayerPacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(sizeof(TReqMovePlayerPacket));
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_uint(packet_buffer, this->dir);
    packet_buffer = pack_uint(packet_buffer, this->player);
    return (int)(packet_buffer - this->raw_packet);
}

void TReqMovePlayerPacket_Unserialize(TReqMovePlayerPacket *this)
{
    unsigned char *packet_buffer;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    packet_buffer = unpack_uint(packet_buffer, &(this->dir));
    unpack_uint(packet_buffer, &(this->player));
}

void TReqMovePlayerPacket_New_Free(TReqMovePlayerPacket *this)
{
    if (this) {
        free(this->raw_packet);
    }
    free(this);
}

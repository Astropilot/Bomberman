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
#include "network/packets/packet_req_startgame.h"
#include "network/network.h"

TReqStartGamePacket *New_TReqStartGamePacket(unsigned char *raw)
{
    TReqStartGamePacket *this = malloc(sizeof(TReqStartGamePacket));

    if(!this) return NULL;

    this->raw_packet = raw;
    this->packet_id = REQ_START_GAME;
    this->Serialize = TReqStartGamePacket_Serialize;
    this->Unserialize = TReqStartGamePacket_Unserialize;
    this->Free = TReqStartGamePacket_New_Free;
    return this;
}

int TReqStartGamePacket_Serialize(TReqStartGamePacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(sizeof(TReqStartGamePacket));
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_uint(packet_buffer, this->player);
    return (packet_buffer - this->raw_packet);
}

void TReqStartGamePacket_Unserialize(TReqStartGamePacket *this)
{
    unsigned char *packet_buffer;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    unpack_uint(packet_buffer, &(this->player));
}

void TReqStartGamePacket_New_Free(TReqStartGamePacket *this)
{
    if (this) {
        free(this->raw_packet);
    }
    free(this);
}

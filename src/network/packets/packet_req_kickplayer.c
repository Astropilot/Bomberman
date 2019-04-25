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
#include "network/packets/packet_req_kickplayer.h"
#include "network/network.h"

TReqKickPlayerPacket *New_TReqKickPlayerPacket(unsigned char *raw)
{
    TReqKickPlayerPacket *this = malloc(sizeof(TReqKickPlayerPacket));

    if(!this) return (NULL);

    this->raw_packet = raw;
    this->packet_id = REQ_KICK_PLAYER;
    this->Serialize = TReqKickPlayerPacket_Serialize;
    this->Unserialize = TReqKickPlayerPacket_Unserialize;
    this->Free = TReqKickPlayerPacket_New_Free;
    return (this);
}

int TReqKickPlayerPacket_Serialize(TReqKickPlayerPacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(sizeof(TReqKickPlayerPacket));
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_uint(packet_buffer, this->player);
    packet_buffer = pack_uint(packet_buffer, this->kick_id);
    return (int)(packet_buffer - this->raw_packet);
}

void TReqKickPlayerPacket_Unserialize(TReqKickPlayerPacket *this)
{
    unsigned char *packet_buffer;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    packet_buffer = unpack_uint(packet_buffer, &(this->player));
    packet_buffer = unpack_uint(packet_buffer, &(this->kick_id));
}

void TReqKickPlayerPacket_New_Free(TReqKickPlayerPacket *this)
{
    if (this) {
        free(this->raw_packet);
    }
    free(this);
}

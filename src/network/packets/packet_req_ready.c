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
#include "network/packets/packet_req_ready.h"
#include "network/network.h"

TReqReadyPacket *New_TReqReadyPacket(unsigned char *raw)
{
    TReqReadyPacket *this = malloc(sizeof(TReqReadyPacket));

    if(!this) return (NULL);

    this->raw_packet = raw;
    this->packet_id = REQ_READY;
    this->Serialize = TReqReadyPacket_Serialize;
    this->Unserialize = TReqReadyPacket_Unserialize;
    this->Free = TReqReadyPacket_New_Free;
    return (this);
}

int TReqReadyPacket_Serialize(TReqReadyPacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(sizeof(TReqReadyPacket));
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_uint(packet_buffer, this->player);
    return (int)(packet_buffer - this->raw_packet);
}

void TReqReadyPacket_Unserialize(TReqReadyPacket *this)
{
    unsigned char *packet_buffer;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    unpack_uint(packet_buffer, &(this->player));
}

void TReqReadyPacket_New_Free(TReqReadyPacket *this)
{
    if (this) {
        free(this->raw_packet);
    }
    free(this);
}

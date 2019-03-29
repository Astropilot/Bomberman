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
#include "network/packets/packet_req_placebomb.h"
#include "network/network.h"

TReqPlaceBombPacket *New_TReqPlaceBombPacket(unsigned char *raw)
{
    TReqPlaceBombPacket *this = malloc(sizeof(TReqPlaceBombPacket));

    if(!this) return (NULL);

    this->raw_packet = raw;
    this->packet_id = REQ_PLACE_BOMB;
    this->Serialize = TReqPlaceBombPacket_Serialize;
    this->Unserialize = TReqPlaceBombPacket_Unserialize;
    this->Free = TReqPlaceBombPacket_New_Free;
    return (this);
}

int TReqPlaceBombPacket_Serialize(TReqPlaceBombPacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(sizeof(TReqPlaceBombPacket));
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_uint(packet_buffer, this->player);
    return (int)(packet_buffer - this->raw_packet);
}

void TReqPlaceBombPacket_Unserialize(TReqPlaceBombPacket *this)
{
    unsigned char *packet_buffer;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    unpack_uint(packet_buffer, &(this->player));
}

void TReqPlaceBombPacket_New_Free(TReqPlaceBombPacket *this)
{
    if (this) {
        free(this->raw_packet);
    }
    free(this);
}

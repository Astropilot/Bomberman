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

#include "core/bomb.h"
#include "network/packets/packet.h"
#include "network/packets/packet_ack_placebomb.h"
#include "network/network.h"

TAckPlaceBombPacket *New_TAckPlaceBombPacket(unsigned char *raw)
{
    TAckPlaceBombPacket *this = malloc(sizeof(TAckPlaceBombPacket));

    if(!this) return NULL;

    this->raw_packet = raw;
    this->packet_id = ACK_PLACE_BOMB;
    this->status = BOMB_POSED;
    this->reason = NO_REASON;
    this->Serialize = TAckPlaceBombPacket_Serialize;
    this->Unserialize = TAckPlaceBombPacket_Unserialize;
    this->Free = TAckPlaceBombPacket_New_Free;
    return this;
}

int TAckPlaceBombPacket_Serialize(TAckPlaceBombPacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(sizeof(TAckPlaceBombPacket));
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_uint(packet_buffer, this->status);
    packet_buffer = pack_uint(packet_buffer, this->reason);
    packet_buffer = pack_uint(packet_buffer, this->bomb_id);
    packet_buffer = pack_uint(packet_buffer, this->x);
    packet_buffer = pack_uint(packet_buffer, this->y);
    return (packet_buffer - this->raw_packet);
}

void TAckPlaceBombPacket_Unserialize(TAckPlaceBombPacket *this)
{
    unsigned char *packet_buffer;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    packet_buffer = unpack_uint(packet_buffer, &(this->status));
    packet_buffer = unpack_uint(packet_buffer, &(this->reason));
    packet_buffer = unpack_uint(packet_buffer, &(this->bomb_id));
    packet_buffer = unpack_uint(packet_buffer, &(this->x));
    unpack_uint(packet_buffer, &(this->y));
}

void TAckPlaceBombPacket_New_Free(TAckPlaceBombPacket *this)
{
    if (this) {
        free(this->raw_packet);
    }
    free(this);
}

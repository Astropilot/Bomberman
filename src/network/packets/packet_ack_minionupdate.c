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

#include "core/utils.h"
#include "network/packets/packet.h"
#include "network/packets/packet_ack_minionupdate.h"
#include "network/network.h"

TAckMinionUpdatePacket *New_TAckMinionUpdatePacket(unsigned char *raw)
{
    TAckMinionUpdatePacket *this = malloc(sizeof(TAckMinionUpdatePacket));

    if(!this) return (NULL);

    this->raw_packet = raw;
    this->packet_id = ACK_MINION_UPDATE;
    this->Serialize = TAckMinionUpdatePacket_Serialize;
    this->Unserialize = TAckMinionUpdatePacket_Unserialize;
    this->Free = TAckMinionUpdatePacket_New_Free;
    return (this);
}

int TAckMinionUpdatePacket_Serialize(TAckMinionUpdatePacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(
        sizeof(TAckMinionUpdatePacket)
    );
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_uint(packet_buffer, this->minion_pos.x);
    packet_buffer = pack_uint(packet_buffer, this->minion_pos.y);

    return (int)(packet_buffer - this->raw_packet);
}

void TAckMinionUpdatePacket_Unserialize(TAckMinionUpdatePacket *this)
{
    unsigned char *packet_buffer;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    packet_buffer = unpack_uint(packet_buffer, &(this->minion_pos.x));
    packet_buffer = unpack_uint(packet_buffer, &(this->minion_pos.y));
}

void TAckMinionUpdatePacket_New_Free(TAckMinionUpdatePacket *this)
{
    if (this) {
        free(this->raw_packet);
    }
    free(this);
}

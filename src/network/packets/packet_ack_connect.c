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
#include "network/packets/packet_ack_connect.h"
#include "network/network.h"

TAckConnectPacket *New_TAckConnectPacket(unsigned char *raw)
{
    TAckConnectPacket *this = malloc(sizeof(TAckConnectPacket));

    if(!this) return (NULL);

    this->raw_packet = raw;
    this->packet_id = ACK_CONNECT;
    this->Serialize = TAckConnectPacket_Serialize;
    this->Unserialize = TAckConnectPacket_Unserialize;
    this->Free = TAckConnectPacket_New_Free;
    return (this);
}

int TAckConnectPacket_Serialize(TAckConnectPacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(sizeof(TAckConnectPacket));
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_int(packet_buffer, this->status);
    packet_buffer = pack_uint(packet_buffer, this->player);
    return (int)(packet_buffer - this->raw_packet);
}

void TAckConnectPacket_Unserialize(TAckConnectPacket *this)
{
    unsigned char *packet_buffer;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    packet_buffer = unpack_int(packet_buffer, &(this->status));
    unpack_uint(packet_buffer, &(this->player));
}

void TAckConnectPacket_New_Free(TAckConnectPacket *this)
{
    if (this) {
        free(this->raw_packet);
    }
    free(this);
}

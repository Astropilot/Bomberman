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

#include "main.h"
#include "core/player.h"
#include "network/packets/packet.h"
#include "network/packets/packet_ack_move.h"
#include "network/network.h"

TAckMovePacket *New_TAckMovePacket(unsigned char *raw)
{
    TAckMovePacket *this = malloc(sizeof(TAckMovePacket));

    if(!this) return NULL;

    this->raw_packet = raw;
    this->packet_id = ACK_MOVE;
    this->Serialize = TAckMovePacket_Serialize;
    this->Unserialize = TAckMovePacket_Unserialize;
    this->Free = TAckMovePacket_New_Free;
    return this;
}

int TAckMovePacket_Serialize(TAckMovePacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(
        sizeof(TAckMovePacket)
    );
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_uint(packet_buffer, this->player_id);

    packet_buffer = pack_uint(packet_buffer, this->player.connected);
    packet_buffer = pack_string(packet_buffer, this->player.username);
    packet_buffer = pack_uint(packet_buffer, this->player.p_id);
    packet_buffer = pack_uint(packet_buffer, this->player.pos.x);
    packet_buffer = pack_uint(packet_buffer, this->player.pos.y);
    packet_buffer = pack_uint(packet_buffer, this->player.direction);
    packet_buffer = pack_uint(packet_buffer, this->take_extra);
    this->player.username = NULL;
    return (packet_buffer - this->raw_packet);
}

void TAckMovePacket_Unserialize(TAckMovePacket *this)
{
    unsigned char *packet_buffer;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    packet_buffer = unpack_uint(packet_buffer, &(this->player_id));

    packet_buffer = unpack_uint(packet_buffer, &(this->player.connected));
    this->player.username = malloc(sizeof(char) * 15);
    packet_buffer = unpack_string(packet_buffer, this->player.username);
    packet_buffer = unpack_uint(packet_buffer, &(this->player.p_id));
    packet_buffer = unpack_uint(packet_buffer, &(this->player.pos.x));
    packet_buffer = unpack_uint(packet_buffer, &(this->player.pos.y));
    packet_buffer = unpack_uint(packet_buffer, &(this->player.direction));
    unpack_uint(packet_buffer, &(this->take_extra));
}

void TAckMovePacket_New_Free(TAckMovePacket *this)
{
    if (this) {
        free(this->player.username);
        free(this->raw_packet);
    }
    free(this);
}

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
#include "network/packets/packet_ack_playerupdate.h"
#include "network/network.h"

TAckPlayerUpdatePacket *New_TAckPlayerUpdatePacket(unsigned char *raw)
{
    TAckPlayerUpdatePacket *this = malloc(sizeof(TAckPlayerUpdatePacket));

    if(!this) return (NULL);

    this->raw_packet = raw;
    this->packet_id = ACK_PLAYER_UPDATE;
    this->Serialize = TAckPlayerUpdatePacket_Serialize;
    this->Unserialize = TAckPlayerUpdatePacket_Unserialize;
    this->Free = TAckPlayerUpdatePacket_New_Free;
    return (this);
}

int TAckPlayerUpdatePacket_Serialize(TAckPlayerUpdatePacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(sizeof(TAckPlayerUpdatePacket));
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);

    packet_buffer = pack_uint(packet_buffer, this->player.connected);
    packet_buffer = pack_string(packet_buffer, this->player.username);
    packet_buffer = pack_uint(packet_buffer, this->player.p_id);
    packet_buffer = pack_uint(packet_buffer, this->player.direction);
    packet_buffer = pack_uint(packet_buffer, this->player.specs.life);
    packet_buffer = pack_uint(packet_buffer, this->player.specs.bombs_capacity);
    packet_buffer = pack_uint(packet_buffer, this->player.specs.bombs_left);
    this->player.username = NULL;
    return (int)(packet_buffer - this->raw_packet);
}

void TAckPlayerUpdatePacket_Unserialize(TAckPlayerUpdatePacket *this)
{
    unsigned char *packet_buffer;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));

    packet_buffer = unpack_uint(packet_buffer, &(this->player.connected));
    this->player.username = malloc(sizeof(char) * 15);
    packet_buffer = unpack_string(packet_buffer, this->player.username);
    packet_buffer = unpack_uint(packet_buffer, &(this->player.p_id));
    packet_buffer = unpack_uint(packet_buffer, &(this->player.direction));

    packet_buffer = unpack_uint(packet_buffer, &(this->player.specs.life));
    packet_buffer = unpack_uint(packet_buffer, &(this->player.specs.bombs_capacity));
    packet_buffer = unpack_uint(packet_buffer, &(this->player.specs.bombs_left));
}

void TAckPlayerUpdatePacket_New_Free(TAckPlayerUpdatePacket *this)
{
    if (this) {
        free(this->player.username);
        free(this->raw_packet);
    }
    free(this);
}

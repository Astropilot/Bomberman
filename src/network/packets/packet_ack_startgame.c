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
#include "network/packets/packet_ack_startgame.h"
#include "network/network.h"

TAckStartGamePacket *New_TAckStartGamePacket(unsigned char *raw)
{
    TAckStartGamePacket *this = malloc(sizeof(TAckStartGamePacket));

    if(!this) return (NULL);

    this->raw_packet = raw;
    this->packet_id = ACK_START_GAME;
    this->Serialize = TAckStartGamePacket_Serialize;
    this->Unserialize = TAckStartGamePacket_Unserialize;
    this->Free = TAckStartGamePacket_New_Free;
    return (this);
}

int TAckStartGamePacket_Serialize(TAckStartGamePacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(sizeof(TAckStartGamePacket));
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    return (int)(packet_buffer - this->raw_packet);
}

void TAckStartGamePacket_Unserialize(TAckStartGamePacket *this)
{
    unsigned char *packet_buffer;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    unpack_int(packet_buffer, &(this->packet_id));
}

void TAckStartGamePacket_New_Free(TAckStartGamePacket *this)
{
    if (this) {
        free(this->raw_packet);
    }
    free(this);
}

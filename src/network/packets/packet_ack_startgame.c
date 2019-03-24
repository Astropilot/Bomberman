/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the ack packet "start game".
*/

#include "network/packets/packet.h"
#include "network/packets/packet_ack_startgame.h"
#include "network/network.h"

TAckStartGamePacket *New_TAckStartGamePacket(unsigned char *raw)
{
    TAckStartGamePacket *this = malloc(sizeof(TAckStartGamePacket));

    if(!this) return NULL;

    this->raw_packet = raw;
    this->packet_id = ACK_START_GAME;
    this->Serialize = TAckStartGamePacket_Serialize;
    this->Unserialize = TAckStartGamePacket_Unserialize;
    this->Free = TAckStartGamePacket_New_Free;
    return this;
}

int TAckStartGamePacket_Serialize(TAckStartGamePacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(sizeof(TAckStartGamePacket));
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    return (packet_buffer - this->raw_packet);
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

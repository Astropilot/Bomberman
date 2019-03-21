/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the ack packet "bomb explode".
*/

#include "network/packets/packet_ack_bombexplode.h"
#include "network/packets/packet.h"
#include "reslib.h"

TAckBombExplodePacket *New_TAckBombExplodePacket(unsigned char *raw)
{
    TAckBombExplodePacket *this = malloc(sizeof(TAckBombExplodePacket));

    if(!this) return NULL;

    this->raw_packet = raw;
    this->packet_id = ACK_BOMB_EXPLODE;
    this->Serialize = TAckBombExplodePacket_Serialize;
    this->Unserialize = TAckBombExplodePacket_Unserialize;
    this->Free = TAckBombExplodePacket_New_Free;
    return this;
}

int TAckBombExplodePacket_Serialize(TAckBombExplodePacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(sizeof(TAckBombExplodePacket));
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_uint(packet_buffer, this->bomb.id);

    packet_buffer = pack_uint(packet_buffer, this->bomb.bomb_pos.x);
    packet_buffer = pack_uint(packet_buffer, this->bomb.bomb_pos.y);

    packet_buffer = pack_uint(packet_buffer, this->bomb.type);
    packet_buffer = pack_uint(packet_buffer, this->bomb.range);
    packet_buffer = pack_uint(packet_buffer, this->bomb.owner_id);
    return (packet_buffer - this->raw_packet);
}

void TAckBombExplodePacket_Unserialize(TAckBombExplodePacket *this)
{
    unsigned char *packet_buffer;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    packet_buffer = unpack_uint(packet_buffer, &(this->bomb.id));

    packet_buffer = unpack_uint(packet_buffer, &(this->bomb.bomb_pos.x));
    packet_buffer = unpack_uint(packet_buffer, &(this->bomb.bomb_pos.y));

    packet_buffer = unpack_uint(packet_buffer, &(this->bomb.type));
    packet_buffer = unpack_uint(packet_buffer, &(this->bomb.range));
    unpack_uint(packet_buffer, &(this->bomb.owner_id));
    this->bomb.time_explode = 0;
}

void TAckBombExplodePacket_New_Free(TAckBombExplodePacket *this)
{
    if (this) {
        free(this->raw_packet);
    }
    free(this);
}

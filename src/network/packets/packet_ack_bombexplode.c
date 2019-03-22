/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the ack packet "bomb explode".
*/

#include "network/packets/packet_ack_bombexplode.h"
#include "network/packets/packet.h"
#include "network/network.h"

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
    unsigned int i;

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

    packet_buffer = pack_uint(packet_buffer, this->destroyed_count);
    for (i = 0; i < this->destroyed_count; i++) {
        packet_buffer = pack_uint(packet_buffer, this->destroyed_walls[i].x);
        packet_buffer = pack_uint(packet_buffer, this->destroyed_walls[i].y);
    }
    packet_buffer = pack_uint(packet_buffer, this->extra_count);
    for (i = 0; i < this->extra_count; i++) {
        packet_buffer = pack_uint(packet_buffer, this->extra_blocks[i].type);
        packet_buffer = pack_uint(packet_buffer, this->extra_blocks[i].pos.x);
        packet_buffer = pack_uint(packet_buffer, this->extra_blocks[i].pos.y);
    }
    return (packet_buffer - this->raw_packet);
}

void TAckBombExplodePacket_Unserialize(TAckBombExplodePacket *this)
{
    unsigned char *packet_buffer;
    unsigned int i;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    packet_buffer = unpack_uint(packet_buffer, &(this->bomb.id));

    packet_buffer = unpack_uint(packet_buffer, &(this->bomb.bomb_pos.x));
    packet_buffer = unpack_uint(packet_buffer, &(this->bomb.bomb_pos.y));

    packet_buffer = unpack_uint(packet_buffer, &(this->bomb.type));
    packet_buffer = unpack_uint(packet_buffer, &(this->bomb.range));
    packet_buffer = unpack_uint(packet_buffer, &(this->bomb.owner_id));
    this->bomb.time_explode = 0;

    packet_buffer = unpack_uint(packet_buffer, &(this->destroyed_count));
    this->destroyed_walls = malloc(sizeof(pos_t) * this->destroyed_count);
    for (i = 0; i < this->destroyed_count; i++) {
        packet_buffer = unpack_uint(packet_buffer, &(this->destroyed_walls[i].x));
        packet_buffer = unpack_uint(packet_buffer, &(this->destroyed_walls[i].y));
    }
    packet_buffer = unpack_uint(packet_buffer, &(this->extra_count));
    this->extra_blocks = malloc(sizeof(pos_t) * this->extra_count);
    for (i = 0; i < this->extra_count; i++) {
        packet_buffer = unpack_uint(packet_buffer, &(this->extra_blocks[i].type));
        packet_buffer = unpack_uint(packet_buffer, &(this->extra_blocks[i].pos.x));
        packet_buffer = unpack_uint(packet_buffer, &(this->extra_blocks[i].pos.y));
    }
}

void TAckBombExplodePacket_New_Free(TAckBombExplodePacket *this)
{
    if (this) {
        if (this->destroyed_count > 0)
            free(this->destroyed_walls);
        if (this->extra_count > 0)
            free(this->extra_blocks);
        free(this->raw_packet);
    }
    free(this);
}

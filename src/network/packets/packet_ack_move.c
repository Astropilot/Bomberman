/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the ack packet "player move".
*/

#include "main.h"
#include "network/packets/packet_ack_move.h"
#include "network/packets/packet.h"
#include "reslib.h"

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
}

void TAckMovePacket_New_Free(TAckMovePacket *this)
{
    if (this) {
        free(this->player.username);
        free(this->raw_packet);
    }
    free(this);
}

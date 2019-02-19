/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the ack packet "place bomb".
*/

#include "network/packets/packet_ack_placebomb.h"
#include "network/packets/packet.h"
#include "reslib.h"

TAckPlaceBombPacket *New_TAckPlaceBombPacket(unsigned char *raw)
{
    TAckPlaceBombPacket *this = malloc(sizeof(TAckPlaceBombPacket));

    if(!this) return NULL;

    this->raw_packet = raw;
    this->packet_id = ACK_PLACE_BOMB;
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

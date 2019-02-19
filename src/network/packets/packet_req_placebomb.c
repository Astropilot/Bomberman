/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the request packet "place bomb".
*/

#include "network/packets/packet_req_placebomb.h"
#include "network/packets/packet.h"
#include "reslib.h"

TReqPlaceBombPacket *New_TReqPlaceBombPacket(unsigned char *raw)
{
    TReqPlaceBombPacket *this = malloc(sizeof(TReqPlaceBombPacket));

    if(!this) return NULL;

    this->raw_packet = raw;
    this->packet_id = REQ_PLACE_BOMB;
    this->Serialize = TReqPlaceBombPacket_Serialize;
    this->Unserialize = TReqPlaceBombPacket_Unserialize;
    this->Free = TReqPlaceBombPacket_New_Free;
    return this;
}

int TReqPlaceBombPacket_Serialize(TReqPlaceBombPacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(sizeof(TReqPlaceBombPacket));
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_uint(packet_buffer, this->player);
    return (packet_buffer - this->raw_packet);
}

void TReqPlaceBombPacket_Unserialize(TReqPlaceBombPacket *this)
{
    unsigned char *packet_buffer;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    unpack_uint(packet_buffer, &(this->player));
}

void TReqPlaceBombPacket_New_Free(TReqPlaceBombPacket *this)
{
    if (this) {
        free(this->raw_packet);
    }
    free(this);
}

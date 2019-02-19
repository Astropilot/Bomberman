/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the request packet "start game".
*/

#include "network/packets/packet_req_startgame.h"
#include "network/packets/packet.h"
#include "reslib.h"

TReqStartGamePacket *New_TReqStartGamePacket(unsigned char *raw)
{
    TReqStartGamePacket *this = malloc(sizeof(TReqStartGamePacket));

    if(!this) return NULL;

    this->raw_packet = raw;
    this->packet_id = REQ_START_GAME;
    this->Serialize = TReqStartGamePacket_Serialize;
    this->Unserialize = TReqStartGamePacket_Unserialize;
    this->Free = TReqStartGamePacket_New_Free;
    return this;
}

int TReqStartGamePacket_Serialize(TReqStartGamePacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(sizeof(TReqStartGamePacket));
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_uint(packet_buffer, this->player);
    return (packet_buffer - this->raw_packet);
}

void TReqStartGamePacket_Unserialize(TReqStartGamePacket *this)
{
    unsigned char *packet_buffer;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    unpack_uint(packet_buffer, &(this->player));
}

void TReqStartGamePacket_New_Free(TReqStartGamePacket *this)
{
    if (this) {
        free(this->raw_packet);
    }
    free(this);
}

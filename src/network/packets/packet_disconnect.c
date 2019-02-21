/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the packets disconnect.
*/

#include "network/packets/packet_disconnect.h"
#include "network/packets/packet.h"
#include "reslib.h"

TReqDisconnectPacket *New_TReqDisconnectPacket(unsigned char *raw)
{
    TReqDisconnectPacket *this = malloc(sizeof(TReqDisconnectPacket));

    if(!this) return NULL;

    this->raw_packet = raw;
    this->packet_id = REQ_DISCONNECT;
    this->Serialize = TReqDisconnectPacket_Serialize;
    this->Unserialize = TReqDisconnectPacket_Unserialize;
    this->Free = TReqDisconnectPacket_New_Free;
    return this;
}

int TReqDisconnectPacket_Serialize(TReqDisconnectPacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(sizeof(TReqDisconnectPacket));
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_int(packet_buffer, this->reason);
    packet_buffer = pack_uint(packet_buffer, this->player);
    return (packet_buffer - this->raw_packet);
}

void TReqDisconnectPacket_Unserialize(TReqDisconnectPacket *this)
{
    unsigned char *packet_buffer;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    packet_buffer = unpack_int(packet_buffer, &(this->reason));
    unpack_uint(packet_buffer, &(this->player));
}

void TReqDisconnectPacket_New_Free(TReqDisconnectPacket *this)
{
    if (this) {
        free(this->raw_packet);
    }
    free(this);
}

TAckDisconnectPacket *New_TAckDisconnectPacket(unsigned char *raw)
{
    TAckDisconnectPacket *this = malloc(sizeof(TAckDisconnectPacket));

    if(!this) return NULL;

    this->raw_packet = raw;
    this->packet_id = ACK_DISCONNECT;
    this->Serialize = TAckDisconnectPacket_Serialize;
    this->Unserialize = TAckDisconnectPacket_Unserialize;
    this->Free = TAckDisconnectPacket_New_Free;
    return this;
}

int TAckDisconnectPacket_Serialize(TAckDisconnectPacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(sizeof(TAckDisconnectPacket));
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_int(packet_buffer, this->reason);
    return (packet_buffer - this->raw_packet);
}

void TAckDisconnectPacket_Unserialize(TAckDisconnectPacket *this)
{
    unsigned char *packet_buffer;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    packet_buffer = unpack_int(packet_buffer, &(this->reason));
}

void TAckDisconnectPacket_New_Free(TAckDisconnectPacket *this)
{
    if (this) {
        free(this->raw_packet);
    }
    free(this);
}
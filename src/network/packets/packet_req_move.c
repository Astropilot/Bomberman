/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the request packet "move player".
*/

#include "network/packets/packet_req_move.h"
#include "reslib.h"

TReqMovePlayerPacket *New_TReqMovePlayerPacket(char *raw)
{
    TReqMovePlayerPacket *this = malloc(sizeof(TReqMovePlayerPacket));

    if(!this) return NULL;

    this->raw_packet = raw;
    this->packet_id = REQ_MOVE;
    this->Serialize = TReqMovePlayerPacket_Serialize;
    this->Unserialize = TReqMovePlayerPacket_Unserialize;
    this->Free = TReqMovePlayerPacket_New_Free;
    return this;
}

int TReqMovePlayerPacket_Serialize(TReqMovePlayerPacket *this)
{
    char *packet_buffer;

    this->raw_packet = malloc(sizeof(TReqMovePlayerPacket));
    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_uint(packet_buffer, this->dir);
    packet_buffer = pack_uint(packet_buffer, this->player);
    return (packet_buffer - this->raw_packet);
}

void TReqMovePlayerPacket_Unserialize(TReqMovePlayerPacket *this)
{
    char *packet_buffer;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    packet_buffer = unpack_uint(packet_buffer, &(this->dir));
    unpack_uint(packet_buffer, &(this->player));
}

void TReqMovePlayerPacket_New_Free(TReqMovePlayerPacket *this)
{
    if (this) {
        free(this->raw_packet);
    }
    free(this);
}

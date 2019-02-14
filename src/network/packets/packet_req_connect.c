/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the request packet "connect".
*/

#include <string.h>

#include "network/packets/packet_req_connect.h"
#include "reslib.h"

TReqConnectPacket *New_TReqConnectPacket(char *raw)
{
    TReqConnectPacket *this = malloc(sizeof(TReqConnectPacket));

    if(!this) return NULL;

    this->raw_packet = raw;
    this->packet_id = REQ_CONNECT;
    this->player_name = NULL;
    this->Serialize = TReqConnectPacket_Serialize;
    this->Unserialize = TReqConnectPacket_Unserialize;
    this->Free = TReqConnectPacket_New_Free;
    return this;
}

int TReqConnectPacket_Serialize(TReqConnectPacket *this)
{
    char *packet_buffer;

    this->raw_packet = malloc(sizeof(TReqConnectPacket) + strlen(this->player_name));
    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_string(packet_buffer, this->player_name);
    return (packet_buffer - this->raw_packet);
}

void TReqConnectPacket_Unserialize(TReqConnectPacket *this)
{
    char *packet_buffer;

    this->player_name = malloc(sizeof(char) * 15);
    if (!this->raw_packet || !this->player_name)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    unpack_string(packet_buffer, &(this->player_name));
}

void TReqConnectPacket_New_Free(TReqConnectPacket *this)
{
    if (this) {
        free(this->raw_packet);
        free(this->player_name);
    }
    free(this);
}

/*******************************************************************************
* PROJECT: Bomberman
*
* AUTHORS: Yohann Martin, Aziz Hamide, Gauthier Desplanque, William Weber
*
* DATE CREATED: 01/16/2019
*
* Copyright (c) 2019 Yohann MARTIN (@Astropilot). All rights reserved.
*
* Licensed under the MIT License. See LICENSE file in the project root for full
* license information.
*******************************************************************************/

#include <string.h>

#include "network/packets/packet.h"
#include "network/packets/packet_req_connect.h"
#include "network/network.h"

TReqConnectPacket *New_TReqConnectPacket(unsigned char *raw)
{
    TReqConnectPacket *this = malloc(sizeof(TReqConnectPacket));

    if(!this) return (NULL);

    this->raw_packet = raw;
    this->packet_id = REQ_CONNECT;
    this->player_name = NULL;
    this->Serialize = TReqConnectPacket_Serialize;
    this->Unserialize = TReqConnectPacket_Unserialize;
    this->Free = TReqConnectPacket_New_Free;
    return (this);
}

int TReqConnectPacket_Serialize(TReqConnectPacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(sizeof(TReqConnectPacket) + strlen(this->player_name));
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_string(packet_buffer, this->player_name);
    return (int)(packet_buffer - this->raw_packet);
}

void TReqConnectPacket_Unserialize(TReqConnectPacket *this)
{
    unsigned char *packet_buffer;

    this->player_name = malloc(sizeof(char) * 15);
    if (!this->raw_packet || !this->player_name)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    unpack_string(packet_buffer, this->player_name);
}

void TReqConnectPacket_New_Free(TReqConnectPacket *this)
{
    if (this) {
        free(this->raw_packet);
        free(this->player_name);
    }
    free(this);
}

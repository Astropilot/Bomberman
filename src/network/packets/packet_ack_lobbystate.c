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

#include "network/packets/packet.h"
#include "network/packets/packet_ack_lobbystate.h"
#include "network/network.h"

TAckLobbyStatePacket *New_TAckLobbyStatePacket(unsigned char *raw)
{
    TAckLobbyStatePacket *this = malloc(sizeof(TAckLobbyStatePacket));

    if(!this) return (NULL);

    this->raw_packet = raw;
    this->packet_id = ACK_LOBBY_STATE;
    this->Serialize = TAckLobbyStatePacket_Serialize;
    this->Unserialize = TAckLobbyStatePacket_Unserialize;
    this->Free = TAckLobbyStatePacket_New_Free;
    return (this);
}

int TAckLobbyStatePacket_Serialize(TAckLobbyStatePacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(sizeof(TAckLobbyStatePacket));
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_uint(packet_buffer, this->nb_players);
    return (int)(packet_buffer - this->raw_packet);
}

void TAckLobbyStatePacket_Unserialize(TAckLobbyStatePacket *this)
{
    unsigned char *packet_buffer;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    unpack_uint(packet_buffer, &(this->nb_players));
}

void TAckLobbyStatePacket_New_Free(TAckLobbyStatePacket *this)
{
    if (this) {
        free(this->raw_packet);
    }
    free(this);
}

/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the ack packet "game state".
*/

#include "core/player.h"
#include "network/packets/packet.h"
#include "network/packets/packet_ack_endgame.h"
#include "network/network.h"

TAckEndGamePacket *New_TAckEndGamePacket(unsigned char *raw)
{
    TAckEndGamePacket *this = malloc(sizeof(TAckEndGamePacket));

    if(!this) return NULL;

    this->raw_packet = raw;
    this->packet_id = ACK_END_GAME;
    this->Serialize = TAckEndGamePacket_Serialize;
    this->Unserialize = TAckEndGamePacket_Unserialize;
    this->Free = TAckEndGamePacket_New_Free;
    return this;
}

int TAckEndGamePacket_Serialize(TAckEndGamePacket *this)
{
    unsigned char *packet_buffer;

    this->raw_packet = malloc(sizeof(TAckEndGamePacket));
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_uint(packet_buffer, this->game_result);

    if (this->game_result == WINNER && this->winner) {
        packet_buffer = pack_uint(packet_buffer, this->winner->connected);
        packet_buffer = pack_string(packet_buffer, this->winner->username);
        packet_buffer = pack_uint(packet_buffer, this->winner->p_id);
        this->winner = NULL;
    }
    return (packet_buffer - this->raw_packet);
}

void TAckEndGamePacket_Unserialize(TAckEndGamePacket *this)
{
    unsigned char *packet_buffer;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    packet_buffer = unpack_uint(packet_buffer, &(this->game_result));

    if (this->game_result == WINNER) {
        this->winner = malloc(sizeof(player_t));
        packet_buffer = unpack_uint(packet_buffer, &(this->winner->connected));
        this->winner->username = malloc(sizeof(char) * 15);
        packet_buffer = unpack_string(packet_buffer, this->winner->username);
        unpack_uint(packet_buffer, &(this->winner->p_id));
    } else
        this->winner = NULL;
}

void TAckEndGamePacket_New_Free(TAckEndGamePacket *this)
{
    if (this) {
        if (this->winner) {
            free(this->winner->username);
            free(this->winner);
        }
        free(this->raw_packet);
    }
    free(this);
}

/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the ack packet "game state".
*/

#include "main.h"
#include "network/packets/packet_ack_gamestate.h"
#include "network/packets/packet.h"
#include "reslib.h"

TAckGameStatePacket *New_TAckGameStatePacket(unsigned char *raw)
{
    TAckGameStatePacket *this = malloc(sizeof(TAckGameStatePacket));

    if(!this) return NULL;

    this->raw_packet = raw;
    this->packet_id = ACK_GAME_STATE;
    this->Serialize = TAckGameStatePacket_Serialize;
    this->Unserialize = TAckGameStatePacket_Unserialize;
    this->Free = TAckGameStatePacket_New_Free;
    return this;
}

int TAckGameStatePacket_Serialize(TAckGameStatePacket *this)
{
    unsigned char *packet_buffer;
    unsigned int i;

    this->raw_packet = malloc(
        sizeof(TAckGameStatePacket) + (sizeof(player_t) * this->nb_players)
    );
    if (!this->raw_packet)
        return 0;
    packet_buffer = this->raw_packet;
    packet_buffer = pack_int(packet_buffer, this->packet_id);
    packet_buffer = pack_uint(packet_buffer, this->nb_players);
    for (i = 0; i < MAX_PLAYERS; i++) {
        if (this->players[i].connected) {
            packet_buffer = pack_uint(packet_buffer, this->players[i].connected);
            packet_buffer = pack_string(packet_buffer, this->players[i].username);
            packet_buffer = pack_uint(packet_buffer, this->players[i].p_id);
            packet_buffer = pack_uint(packet_buffer, this->players[i].x);
            packet_buffer = pack_uint(packet_buffer, this->players[i].y);
            packet_buffer = pack_uint(packet_buffer, this->players[i].direction);
        }
    }
    this->nb_players = 0;
    this->players = NULL;
    return (packet_buffer - this->raw_packet);
}

void TAckGameStatePacket_Unserialize(TAckGameStatePacket *this)
{
    unsigned char *packet_buffer;
    unsigned int i;

    if (!this->raw_packet)
        return;
    packet_buffer = this->raw_packet;
    packet_buffer = unpack_int(packet_buffer, &(this->packet_id));
    packet_buffer = unpack_uint(packet_buffer, &(this->nb_players));
    this->players = malloc(sizeof(player_t) * this->nb_players);
    for (i = 0; i < this->nb_players; i++) {
        packet_buffer = unpack_uint(packet_buffer, &(this->players[i].connected));
        this->players[i].username = malloc(sizeof(char) * 15);
        packet_buffer = unpack_string(packet_buffer, this->players[i].username);
        packet_buffer = unpack_uint(packet_buffer, &(this->players[i].p_id));
        packet_buffer = unpack_uint(packet_buffer, &(this->players[i].x));
        packet_buffer = unpack_uint(packet_buffer, &(this->players[i].y));
        packet_buffer = unpack_uint(packet_buffer, &(this->players[i].direction));
    }
}

void TAckGameStatePacket_New_Free(TAckGameStatePacket *this)
{
    if (this) {
        unsigned int i;

        for (i = 0; i < this->nb_players; i++) {
            free(this->players[i].username);
        }
        free(this->players);
        free(this->raw_packet);
    }
    free(this);
}

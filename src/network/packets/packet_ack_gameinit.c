/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the ack packet "game state".
*/

#include "main.h"
#include "network/packets/packet_ack_gameinit.h"
#include "network/packets/packet.h"
#include "reslib.h"

TAckGameInitPacket *New_TAckGameInitPacket(unsigned char *raw)
{
    TAckGameInitPacket *this = malloc(sizeof(TAckGameInitPacket));

    if(!this) return NULL;

    this->raw_packet = raw;
    this->packet_id = ACK_GAME_INIT;
    this->Serialize = TAckGameInitPacket_Serialize;
    this->Unserialize = TAckGameInitPacket_Unserialize;
    this->Free = TAckGameInitPacket_New_Free;
    return this;
}

int TAckGameInitPacket_Serialize(TAckGameInitPacket *this)
{
    unsigned char *packet_buffer;
    unsigned int i;
    unsigned int j;

    this->raw_packet = malloc(
        sizeof(TAckGameInitPacket) + (sizeof(player_t) * this->nb_players) +
        (sizeof(object_type_t) * (MAP_WIDTH * MAP_HEIGHT))
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
            packet_buffer = pack_uint(packet_buffer, this->players[i].pos.x);
            packet_buffer = pack_uint(packet_buffer, this->players[i].pos.y);
            packet_buffer = pack_uint(packet_buffer, this->players[i].direction);
        }
    }
    for (i = 0; i < MAP_HEIGHT; i++) {
        for (j = 0; j < MAP_WIDTH; j++) {
            packet_buffer = pack_uint(packet_buffer, this->block_map[i][j]);
        }
    }
    this->block_map = NULL;
    this->nb_players = 0;
    this->players = NULL;
    return (packet_buffer - this->raw_packet);
}

void TAckGameInitPacket_Unserialize(TAckGameInitPacket *this)
{
    unsigned char *packet_buffer;
    unsigned int i;
    unsigned int j;

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
        packet_buffer = unpack_uint(packet_buffer, &(this->players[i].pos.x));
        packet_buffer = unpack_uint(packet_buffer, &(this->players[i].pos.y));
        packet_buffer = unpack_uint(packet_buffer, &(this->players[i].direction));
    }
    this->block_map = malloc(MAP_HEIGHT * sizeof(object_type_t*));
    for (i = 0; i < MAP_HEIGHT; i++) {
        this->block_map[i] = malloc(MAP_WIDTH * sizeof(object_type_t));
    }
    for (i = 0; i < MAP_HEIGHT; i++) {
        for (j = 0; j < MAP_WIDTH; j++) {
            packet_buffer = unpack_uint(packet_buffer, &(this->block_map[i][j]));
        }
    }
}

void TAckGameInitPacket_New_Free(TAckGameInitPacket *this)
{
    if (this) {
        unsigned int i;

        if (this->block_map) {
            for (i = 0; i < MAP_HEIGHT; i++) {
                free(this->block_map[i]);
            }
            free(this->block_map);
        }
        for (i = 0; i < this->nb_players; i++) {
            free(this->players[i].username);
        }
        free(this->players);
        free(this->raw_packet);
    }
    free(this);
}

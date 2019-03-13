/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the ack packet "game state".
*/

#ifndef PACKET_ACK_GAMESTATE_H_
#define PACKET_ACK_GAMESTATE_H_

#include <stdlib.h>

#include "core/player.h"
#include "core/map.h"

typedef struct TAckGameStatePacket {

    int(*Serialize)(struct TAckGameStatePacket*);

    void(*Unserialize)(struct TAckGameStatePacket*);

    void(*Free)(struct TAckGameStatePacket*);

    unsigned char *raw_packet;
    int packet_id;
    unsigned int nb_players;
    unsigned int first_init;
    player_t *players;
    object_type_t **block_map;


} TAckGameStatePacket ;

TAckGameStatePacket *New_TAckGameStatePacket(unsigned char *raw);
int TAckGameStatePacket_Serialize(TAckGameStatePacket *this);
void TAckGameStatePacket_Unserialize(TAckGameStatePacket *this);
void TAckGameStatePacket_New_Free(TAckGameStatePacket *this);

#endif

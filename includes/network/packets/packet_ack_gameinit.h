/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the ack packet "game init".
*/

#ifndef PACKET_ACK_GAMEINIT_H_
#define PACKET_ACK_GAMEINIT_H_

#include <stdlib.h>

#include "core/player.h"
#include "core/map.h"

typedef struct TAckGameInitPacket {

    int(*Serialize)(struct TAckGameInitPacket*);

    void(*Unserialize)(struct TAckGameInitPacket*);

    void(*Free)(struct TAckGameInitPacket*);

    unsigned char *raw_packet;
    int packet_id;
    unsigned int nb_players;
    player_t *players;
    object_type_t **block_map;


} TAckGameInitPacket ;

TAckGameInitPacket *New_TAckGameInitPacket(unsigned char *raw);
int TAckGameInitPacket_Serialize(TAckGameInitPacket *this);
void TAckGameInitPacket_Unserialize(TAckGameInitPacket *this);
void TAckGameInitPacket_New_Free(TAckGameInitPacket *this);

#endif

/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the ack packet "bomb explode".
*/

#ifndef PACKET_ACK_BOMBEXPLODE_H_
#define PACKET_ACK_BOMBEXPLODE_H_

#include <stdlib.h>

#include "core/utils.h"

typedef struct TAckBombExplodePacket {

    int(*Serialize)(struct TAckBombExplodePacket*);

    void(*Unserialize)(struct TAckBombExplodePacket*);

    void(*Free)(struct TAckBombExplodePacket*);

    unsigned char *raw_packet;
    int packet_id;
    bomb_t bomb;
    object_t *destroyed_blocks;

} TAckBombExplodePacket ;

TAckBombExplodePacket *New_TAckBombExplodePacket(unsigned char *raw);
int TAckBombExplodePacket_Serialize(TAckBombExplodePacket *this);
void TAckBombExplodePacket_Unserialize(TAckBombExplodePacket *this);
void TAckBombExplodePacket_New_Free(TAckBombExplodePacket *this);

#endif

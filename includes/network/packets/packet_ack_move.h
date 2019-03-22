/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the ack packet "player move".
*/

#ifndef PACKET_ACK_MOVE_H_
#define PACKET_ACK_MOVE_H_

#include <stdlib.h>

#include "core/player.h"

typedef struct TAckMovePacket {

    int(*Serialize)(struct TAckMovePacket*);

    void(*Unserialize)(struct TAckMovePacket*);

    void(*Free)(struct TAckMovePacket*);

    unsigned char *raw_packet;
    int packet_id;
    unsigned int player_id;
    player_t player;


} TAckMovePacket ;

TAckMovePacket *New_TAckMovePacket(unsigned char *raw);
int TAckMovePacket_Serialize(TAckMovePacket *this);
void TAckMovePacket_Unserialize(TAckMovePacket *this);
void TAckMovePacket_New_Free(TAckMovePacket *this);

#endif

/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the ack packet "player update".
*/

#ifndef PACKET_ACK_PLAYERUPDATE_H_
#define PACKET_ACK_PLAYERUPDATE_H_

#include "core/player.h"

typedef struct TAckPlayerUpdatePacket {

    int(*Serialize)(struct TAckPlayerUpdatePacket*);

    void(*Unserialize)(struct TAckPlayerUpdatePacket*);

    void(*Free)(struct TAckPlayerUpdatePacket*);

    unsigned char *raw_packet;
    int packet_id;
    player_t player;

} TAckPlayerUpdatePacket ;

TAckPlayerUpdatePacket *New_TAckPlayerUpdatePacket(unsigned char *raw);
int TAckPlayerUpdatePacket_Serialize(TAckPlayerUpdatePacket *this);
void TAckPlayerUpdatePacket_Unserialize(TAckPlayerUpdatePacket *this);
void TAckPlayerUpdatePacket_New_Free(TAckPlayerUpdatePacket *this);

#endif

/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the ack packet "place bomb".
*/

#ifndef PACKET_ACK_PLACEBOMB_H_
#define PACKET_ACK_PLACEBOMB_H_

#include <stdlib.h>

#include "core/bomb.h"

typedef struct TAckPlaceBombPacket {

    int(*Serialize)(struct TAckPlaceBombPacket*);

    void(*Unserialize)(struct TAckPlaceBombPacket*);

    void(*Free)(struct TAckPlaceBombPacket*);

    unsigned char *raw_packet;
    int packet_id;
    bomb_status_t status;
    bomb_reason_t reason;
    unsigned int bomb_id;
    unsigned int x;
    unsigned int y;

} TAckPlaceBombPacket ;

TAckPlaceBombPacket *New_TAckPlaceBombPacket(unsigned char *raw);
int TAckPlaceBombPacket_Serialize(TAckPlaceBombPacket *this);
void TAckPlaceBombPacket_Unserialize(TAckPlaceBombPacket *this);
void TAckPlaceBombPacket_New_Free(TAckPlaceBombPacket *this);

#endif

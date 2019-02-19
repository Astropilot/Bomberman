/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the ack packet "start game".
*/

#ifndef PACKET_ACK_STARTGAME_H_
#define PACKET_ACK_STARTGAME_H_

#include <stdlib.h>

typedef struct TAckStartGamePacket {

    int(*Serialize)(struct TAckStartGamePacket*);

    void(*Unserialize)(struct TAckStartGamePacket*);

    void(*Free)(struct TAckStartGamePacket*);

    unsigned char *raw_packet;
    int packet_id;

} TAckStartGamePacket ;

TAckStartGamePacket *New_TAckStartGamePacket(unsigned char *raw);
int TAckStartGamePacket_Serialize(TAckStartGamePacket *this);
void TAckStartGamePacket_Unserialize(TAckStartGamePacket *this);
void TAckStartGamePacket_New_Free(TAckStartGamePacket *this);

#endif

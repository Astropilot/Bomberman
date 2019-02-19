/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the request packet "ready".
*/

#ifndef PACKET_REQ_READY_H_
#define PACKET_REQ_READY_H_

#include <stdlib.h>

typedef struct TReqReadyPacket {

    int(*Serialize)(struct TReqReadyPacket*);

    void(*Unserialize)(struct TReqReadyPacket*);

    void(*Free)(struct TReqReadyPacket*);

    unsigned char *raw_packet;
    int packet_id;
    unsigned int player;

} TReqReadyPacket ;

TReqReadyPacket *New_TReqReadyPacket(unsigned char *raw);
int TReqReadyPacket_Serialize(TReqReadyPacket *this);
void TReqReadyPacket_Unserialize(TReqReadyPacket *this);
void TReqReadyPacket_New_Free(TReqReadyPacket *this);

#endif

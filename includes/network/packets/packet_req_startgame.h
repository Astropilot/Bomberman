/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the request packet "start game".
*/

#ifndef PACKET_REQ_STARTGAME_H_
#define PACKET_REQ_STARTGAME_H_

#include <stdlib.h>

#include "network/packets/packet.h"

typedef struct TReqStartGamePacket {

    int(*Serialize)(struct TReqStartGamePacket*);

    void(*Unserialize)(struct TReqStartGamePacket*);

    void(*Free)(struct TReqStartGamePacket*);

    char *raw_packet;
    packet_t packet_id;
    unsigned int player;

} TReqStartGamePacket ;

TReqStartGamePacket *New_TReqStartGamePacket(char *raw);
int TReqStartGamePacket_Serialize(TReqStartGamePacket *this);
void TReqStartGamePacket_Unserialize(TReqStartGamePacket *this);
void TReqStartGamePacket_New_Free(TReqStartGamePacket *this);

#endif

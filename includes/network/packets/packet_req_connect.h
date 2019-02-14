/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the request packet "connect".
*/

#ifndef PACKET_REQ_CONNECT_H_
#define PACKET_REQ_CONNECT_H_

#include <stdlib.h>

#include "network/packets/packet.h"

typedef struct TReqConnectPacket {

    int(*Serialize)(struct TReqConnectPacket*);

    void(*Unserialize)(struct TReqConnectPacket*);

    void(*Free)(struct TReqConnectPacket*);

    char *raw_packet;
    packet_t packet_id;
    char *player_name;

} TReqConnectPacket ;

TReqConnectPacket *New_TReqConnectPacket(char *raw);
int TReqConnectPacket_Serialize(TReqConnectPacket *this);
void TReqConnectPacket_Unserialize(TReqConnectPacket *this);
void TReqConnectPacket_New_Free(TReqConnectPacket *this);

#endif

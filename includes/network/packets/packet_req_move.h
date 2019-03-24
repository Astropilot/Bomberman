/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the request packet "move player".
*/

#ifndef PACKET_REQ_MOVEPLAYER_H_
#define PACKET_REQ_MOVEPLAYER_H_

typedef struct TReqMovePlayerPacket {

    int(*Serialize)(struct TReqMovePlayerPacket*);

    void(*Unserialize)(struct TReqMovePlayerPacket*);

    void(*Free)(struct TReqMovePlayerPacket*);

    unsigned char *raw_packet;
    int packet_id;
    unsigned int dir;
    unsigned int player;

} TReqMovePlayerPacket ;

TReqMovePlayerPacket *New_TReqMovePlayerPacket(unsigned char *raw);
int TReqMovePlayerPacket_Serialize(TReqMovePlayerPacket *this);
void TReqMovePlayerPacket_Unserialize(TReqMovePlayerPacket *this);
void TReqMovePlayerPacket_New_Free(TReqMovePlayerPacket *this);

#endif

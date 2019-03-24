/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the request packet "place bomb".
*/

#ifndef PACKET_REQ_PLACEBOMB_H_
#define PACKET_REQ_PLACEBOMB_H_

typedef struct TReqPlaceBombPacket {

    int(*Serialize)(struct TReqPlaceBombPacket*);

    void(*Unserialize)(struct TReqPlaceBombPacket*);

    void(*Free)(struct TReqPlaceBombPacket*);

    unsigned char *raw_packet;
    int packet_id;
    unsigned int player;

} TReqPlaceBombPacket ;

TReqPlaceBombPacket *New_TReqPlaceBombPacket(unsigned char *raw);
int TReqPlaceBombPacket_Serialize(TReqPlaceBombPacket *this);
void TReqPlaceBombPacket_Unserialize(TReqPlaceBombPacket *this);
void TReqPlaceBombPacket_New_Free(TReqPlaceBombPacket *this);

#endif

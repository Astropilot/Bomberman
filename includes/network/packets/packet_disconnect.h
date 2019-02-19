/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the packets disconnect.
*/

#ifndef PACKET_DISCONNECT_H_
#define PACKET_DISCONNECT_H_

#include <stdlib.h>

typedef enum leave_reason_e {
    USER_QUIT,
    MASTER_LEAVE
} leave_reason_t ;

typedef struct TReqDisconnectPacket {

    int(*Serialize)(struct TReqDisconnectPacket*);

    void(*Unserialize)(struct TReqDisconnectPacket*);

    void(*Free)(struct TReqDisconnectPacket*);

    unsigned char *raw_packet;
    int packet_id;
    int reason;
    unsigned int player;

} TReqDisconnectPacket ;

TReqDisconnectPacket *New_TReqDisconnectPacket(unsigned char *raw);
int TReqDisconnectPacket_Serialize(TReqDisconnectPacket *this);
void TReqDisconnectPacket_Unserialize(TReqDisconnectPacket *this);
void TReqDisconnectPacket_New_Free(TReqDisconnectPacket *this);

typedef struct TAckDisconnectPacket {

    int(*Serialize)(struct TAckDisconnectPacket*);

    void(*Unserialize)(struct TAckDisconnectPacket*);

    void(*Free)(struct TAckDisconnectPacket*);

    unsigned char *raw_packet;
    int packet_id;
    int reason;

} TAckDisconnectPacket ;

TAckDisconnectPacket *New_TAckDisconnectPacket(unsigned char *raw);
int TAckDisconnectPacket_Serialize(TAckDisconnectPacket *this);
void TAckDisconnectPacket_Unserialize(TAckDisconnectPacket *this);
void TAckDisconnectPacket_New_Free(TAckDisconnectPacket *this);

#endif

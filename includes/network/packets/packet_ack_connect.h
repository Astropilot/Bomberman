/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the ack packet "connect".
*/

#ifndef PACKET_ACK_CONNECT_H_
#define PACKET_ACK_CONNECT_H_

#include <stdlib.h>

typedef enum connect_status_e {
    OK,
    GAME_FULL,
    GAME_STARTED,
    UNDEFINED
} connect_status_t ;

typedef struct TAckConnectPacket {

    int(*Serialize)(struct TAckConnectPacket*);

    void(*Unserialize)(struct TAckConnectPacket*);

    void(*Free)(struct TAckConnectPacket*);

    unsigned char *raw_packet;
    int packet_id;
    int status;
    unsigned int player;

} TAckConnectPacket ;

TAckConnectPacket *New_TAckConnectPacket(unsigned char *raw);
int TAckConnectPacket_Serialize(TAckConnectPacket *this);
void TAckConnectPacket_Unserialize(TAckConnectPacket *this);
void TAckConnectPacket_New_Free(TAckConnectPacket *this);

#endif

/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the packet class.
*/

#ifndef NETWORK_PACKET_H_
#define NETWORK_PACKET_H_

#include "network/network.h"

typedef enum packet_e {
    REQ_CONNECT      = 0x01,
    REQ_DISCONNECT   = 0x02,
    REQ_START_GAME   = 0x03,
    REQ_PLACE_BOMB   = 0x04,
    REQ_MOVE         = 0x05,
    REQ_READY        = 0x06,
    ACK_CONNECT      = 0x07,
    ACK_DISCONNECT   = 0x08,
    ACK_LOBBY_STATE  = 0x09,
    ACK_START_GAME   = 0x0A,
    ACK_GAME_INIT    = 0x0B,
    ACK_MOVE         = 0x0C,
    ACK_PLACE_BOMB   = 0x0D,
    ACK_BOMB_EXPLODE = 0x0E
} packet_t;

typedef struct TPacket {

    int(*Serialize)(struct TPacket*);

    void(*Unserialize)(struct TPacket*);

    void(*Free)(struct TPacket*);

    unsigned char *raw_packet;

} TPacket ;

int extract_packet_id(unsigned char *raw_packet);
TMessage packet_to_message(TPacket *packet);

#endif

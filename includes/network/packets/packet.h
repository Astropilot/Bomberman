/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the packet class.
*/

#ifndef NETWORK_PACKET_H_
#define NETWORK_PACKET_H_

#include <stdlib.h>

typedef enum packet_e {
    REQ_CONNECT     = 0x01,
    REQ_DISCONNECT  = 0x02,
    REQ_START_GAME  = 0x03,
    REQ_PLACE_BOMB  = 0x04,
    REQ_MOVE        = 0x05;
    ACK_CONNECT     = 0x06,
    ACK_DISCONNECT  = 0x07,
    ACK_LOBBY_STATE = 0x08
    //ACK_START_GAME  = 0x09,
    //ACK_GAME_STATE  = 0x0A
} packet_t;

int extract_packet_id(char *raw_packet);

/*
ack_start_game = 0x03
{

}

ack_game_state = 0x04
{
    // Players state
    // Map state
    // Game state
}

*/

#endif

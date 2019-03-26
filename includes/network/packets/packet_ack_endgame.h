/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the ack packet "end game".
*/

#ifndef PACKET_ACK_ENDGAME_H_
#define PACKET_ACK_ENDGAME_H_

#include "core/player.h"

typedef enum game_result_e {
    WINNER,
    DRAW
} game_result_t ;

typedef struct TAckEndGamePacket {

    int(*Serialize)(struct TAckEndGamePacket*);

    void(*Unserialize)(struct TAckEndGamePacket*);

    void(*Free)(struct TAckEndGamePacket*);

    unsigned char *raw_packet;
    int packet_id;
    unsigned int game_result;
    player_t *winner;

} TAckEndGamePacket ;

TAckEndGamePacket *New_TAckEndGamePacket(unsigned char *raw);
int TAckEndGamePacket_Serialize(TAckEndGamePacket *this);
void TAckEndGamePacket_Unserialize(TAckEndGamePacket *this);
void TAckEndGamePacket_New_Free(TAckEndGamePacket *this);

#endif

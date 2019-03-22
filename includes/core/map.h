/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the game map class.
*/

#ifndef CORE_MAP_H_
#define CORE_MAP_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "main.h"
#include "core/player.h"
#include "core/utils.h"
#include "core/bomb.h"

typedef struct TAckBombExplodePacket TAckBombExplodePacket;

typedef enum object_type_e {
    NOTHING,
    WALL,
    BREAKABLE_WALL,
    BONUS_RANGE,
    MALUS_RANGE,
    BONUS_CAPACITY,
    MALUS_CAPACITY,
    BONUS_SPEED,
    MALUS_SPEED
} object_type_t ;

typedef struct object_s {

    object_type_t type;
    pos_t pos;

} object_t ;

typedef struct TMap {

    void(*Generate)(struct TMap*);

    unsigned int(*Move_Player)(struct TMap*, unsigned int, direction_t);

    bomb_status_t(*Place_Bomb)(struct TMap*, unsigned int, bomb_reason_t*);

    void(*Explose_Bomb)(struct TMap*, bomb_t*, TAckBombExplodePacket*);

    void(*Free)(struct TMap*);

    object_type_t **block_map;
    size_t max_players;
    player_t *players;
    bomb_node_t *bombs_head;
    unsigned int bomb_offset;

} TMap ;

TMap *New_TMap(size_t max_clients);
void TMap_Generate(TMap *this);
unsigned int TMap_Move_Player(TMap *this, unsigned int player_id, direction_t direction);
bomb_status_t TMap_Place_Bomb(TMap *this, unsigned int player_id, bomb_reason_t *reason);
void TMap_Explose_Bomb(TMap *this, bomb_t *bomb, TAckBombExplodePacket *packet);
void TMap_New_Free(TMap *this);

#endif

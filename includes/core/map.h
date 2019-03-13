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

typedef enum object_type_e {
    NOTHING,
    WALL,
    BREAKABLE_WALL,
    BOMB,
    BONUS_LIFE
} object_type_t ;

typedef struct TMap {

    void(*Generate)(struct TMap*);

    void(*Move_Player)(struct TMap*, unsigned int, direction_t);

    void(*Free)(struct TMap*);

    object_type_t **block_map;
    player_t *players;
//  bomb_t *bombs;

} TMap ;

TMap *New_TMap(size_t max_clients);
void TMap_Generate(TMap *this);
void TMap_Move_Player(TMap *this, unsigned int player_id, direction_t direction);
void TMap_New_Free(TMap *this);

#endif

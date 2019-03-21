/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the game bomb class.
*/

#ifndef CORE_BOMB_H_
#define CORE_BOMB_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "main.h"
#include "core/utils.h"

typedef enum bomb_status_e {
    BOMB_POSED,
    BOMB_CANCELED
} bomb_status_t ;

typedef enum bomb_reason_e {
    ALREADY_ITEM,
    NO_MORE_CAPACITY,
    INTERNAL_ERROR,
    NO_REASON
} bomb_reason_t ;

typedef enum bomb_type_e {
    CLASSIC
    //SQUARE
} bomb_type_t ;

typedef struct bomb_s {

    unsigned int id;
    pos_t bomb_pos;
    unsigned int type;
    unsigned int range;
    unsigned int time_explode;
    unsigned int owner_id;

} bomb_t ;

typedef struct bomb_node_s {

    bomb_t *bomb;
    struct bomb_node_s *next;

} bomb_node_t ;

void add_bomb(bomb_node_t **bombs_head, bomb_t *bomb);
void remove_bomb(bomb_node_t **bombs_head, bomb_t *bomb);

#endif

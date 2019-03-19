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


typedef struct bomb_s {

    pos_t bomb_pos;
    unsigned int type;
    unsigned int range;

} bomb_t ;

typedef struct bomb_node_s {

    bomb_t *bomb;
    struct bomb_node_s *next;

} bomb_node_t ;

#endif

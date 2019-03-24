/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the player class.
*/

#ifndef CORE_PLAYER_H_
#define CORE_PLAYER_H_

#include <stdlib.h>
#include <string.h>

#include "core/bomb.h"
#include "core/utils.h"

typedef enum direction_e {
    NORD,
    OUEST,
    EST,
    SUD
} direction_t ;

typedef struct player_specs_s {

    unsigned int life;
    unsigned int move_speed;
    unsigned int bombs_capacity;
    unsigned int bombs_left;
    unsigned int bombs_range;

} player_specs_t ;

typedef struct player_s {

    unsigned int connected;
    char *username;
    unsigned int p_id;
    pos_t pos;
    unsigned int direction;
    player_specs_t specs;
    unsigned int last_move_time;

} player_t ;

unsigned int next_id(player_t *players);
void init_player(player_t *player, int id, const char *username);
void reset_player(player_t *player);

#endif

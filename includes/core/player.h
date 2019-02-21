/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the player class.
*/

#ifndef CORE_PLAYER_H_
#define CORE_PLAYER_H_

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef enum direction_e {
    NORD,
    OUEST,
    EST,
    SUD
} direction_t ;

typedef struct player_s {

    unsigned int connected;
    char *username;
    unsigned int p_id;
    unsigned int x;
    unsigned int y;
    unsigned int direction;

} player_t ;

unsigned int next_id(player_t *players);
void init_player(player_t *player, int id, const char *username);
void move_player(player_t *player, direction_t direction);
void reset_player(player_t *player);

#endif

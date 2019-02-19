/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the player class.
*/

#include "core/player.h"

void init_player(player_t *player, int id, const char *username)
{
    player->username = strdup(username);
    switch (id) {
        case 0:
            player->x = 50;
            player->y = 50;
            player->direction = (unsigned int)EST;
            break;
        case 1:
            player->x = 700;
            player->y = 50;
            player->direction = (unsigned int)OUEST;
            break;
        case 2:
            player->x = 50;
            player->y = 400;
            player->direction = (unsigned int)EST;
            break;
        case 3:
            player->x = 700;
            player->y = 400;
            player->direction = (unsigned int)OUEST;
            break;
    }
}

void move_player(player_t *player, direction_t direction)
{
    unsigned int speed_player = 7;
    switch (direction) {
        case OUEST:
            player->x = player->x - speed_player;
            break;
        case EST:
            player->x = player->x + speed_player;
            break;
        case NORD:
            player->y = player->y - speed_player;
            break;
        case SUD:
            player->y = player->y + speed_player;
            break;
    }
    player->direction = (unsigned int)direction;
}

void reset_player(player_t *player)
{
    free(player->username);
}

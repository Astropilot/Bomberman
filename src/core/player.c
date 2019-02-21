/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the player class.
*/

#include "main.h"
#include "core/player.h"

unsigned int next_id(player_t *players)
{
    unsigned int i;

    for (i = 0; i < MAX_PLAYERS; i++) {
        if (!players[i].connected)
            return (i);
    }
    return (MAX_PLAYERS + 1);
}

void init_player(player_t *player, int id, const char *username)
{
    player->connected = 1;
    player->username = strdup(username);
    player->p_id = (unsigned int)id;
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
    player->connected = 0;
    free(player->username);
    player->username = NULL;
}

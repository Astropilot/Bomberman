/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the player class.
*/

#include "main.h"
#include "core/player.h"
#include "core/utils.h"

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
    player->speed = 400;
    player->last_move_time = 0;
    switch (id) {
        case 0:
            map_to_pix(0, 0, (int *)&(player->pos.x), (int *)&(player->pos.y));
            player->direction = (unsigned int)EST;
            break;
        case 1:
            map_to_pix(MAP_WIDTH - 1, 0, (int *)&(player->pos.x), (int *)&(player->pos.y));
            player->direction = (unsigned int)OUEST;
            break;
        case 2:
            map_to_pix(0, MAP_HEIGHT - 1, (int *)&(player->pos.x), (int *)&(player->pos.y));
            player->direction = (unsigned int)EST;
            break;
        case 3:
            map_to_pix(MAP_WIDTH - 1, MAP_HEIGHT - 1, (int *)&(player->pos.x), (int *)&(player->pos.y));
            player->direction = (unsigned int)OUEST;
            break;
    }
}

void reset_player(player_t *player)
{
    player->connected = 0;
    free(player->username);
    player->username = NULL;
}

/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the game map class.
*/

#include <SDL2/SDL.h>

#include "core/map.h"
#include "core/utils.h"

static void TMap_Init(TMap *this, size_t max_clients);

TMap *New_TMap(size_t max_clients)
{
    TMap *this = malloc(sizeof(TMap));

    if(!this) return NULL;

    TMap_Init(this, max_clients);
    this->Free = TMap_New_Free;
    return this;
}

static void TMap_Init(TMap *this, size_t max_clients)
{
    unsigned int i;
    unsigned int j;

    this->Generate = TMap_Generate;
    this->Move_Player = TMap_Move_Player;
    this->block_map = malloc(MAP_HEIGHT * sizeof(object_type_t*));
    for (i = 0; i < MAP_HEIGHT; i++) {
        this->block_map[i] = malloc(MAP_WIDTH * sizeof(object_type_t));
        for (j = 0; j < MAP_WIDTH; j++) {
            this->block_map[i][j] = NOTHING;
        }
    }
    this->players = malloc(sizeof(player_t) * max_clients);
    for (i = 0; i < max_clients; i++) {
        this->players[i].connected = 0;
    }
    this->bombs_head = NULL;
}

void TMap_Generate(TMap *this)
{
    unsigned int y;
    unsigned int x;

    for (y = 0; y < MAP_HEIGHT; y++) {
        for (x = 0; x < MAP_WIDTH; x++) {
            if (y % 2 != 0 && x % 2 != 0) { // Si emplacement pour un mur
                this->block_map[y][x] = WALL;
            } else if (
                        (y > 1 || x > 1) &&
                        (y < MAP_HEIGHT - 2 || x > 1) &&
                        (y > 1 || x < MAP_WIDTH - 2) &&
                        (y < MAP_HEIGHT - 2 || x < MAP_WIDTH - 2)
                      ) {
                if (rand_int(100) <= CHANCE_BREAKABLE_WALL) { // Si chance d'avoir un mur cassable
                    this->block_map[y][x] = BREAKABLE_WALL;
                }
            }
        }
    }
}

void TMap_Move_Player(TMap *this, unsigned int player_id, direction_t direction)
{
    player_t *player = &(this->players[player_id]);
    pos_t new_coords = player->pos;
    int block_x, block_y;
    unsigned int current_time = SDL_GetTicks();

    if (current_time <= player->last_move_time + player->speed)
        return;
    player->last_move_time = current_time;
    player->direction = (unsigned int)direction;
    if (direction == OUEST || direction == EST)
        new_coords.x = new_coords.x + (direction == EST ? MAP_BLOCK_SIZE : -MAP_BLOCK_SIZE);
    else
        new_coords.y = new_coords.y + (direction == SUD ? MAP_BLOCK_SIZE : -MAP_BLOCK_SIZE);
    pix_to_map((int)new_coords.x, (int)new_coords.y, &block_x, &block_y);

    // Gestion des collisions.
    if (block_x < 0 || block_x >= MAP_WIDTH) return;
    if (block_y < 0 || block_y >= MAP_HEIGHT) return;
    if (this->block_map[block_y][block_x] != NOTHING) return;

    player->pos.x = new_coords.x;
    player->pos.y = new_coords.y;
}

void TMap_New_Free(TMap *this)
{
    if (this) {
        unsigned int i;

        for (i = 0; i < MAP_HEIGHT; i++) {
            free(this->block_map[i]);
        }
        free(this->block_map);
        this->block_map = NULL;

        free(this->players);
        this->players = NULL;
    }
    free(this);
}

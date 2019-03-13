/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the game map class.
*/

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
    unsigned int speed = 7;
    pos_t new_coords = player->pos;

    player->direction = (unsigned int)direction;
    if (direction == OUEST || direction == EST)
        new_coords.x = new_coords.x + (direction == EST ? speed : -speed);
    else
        new_coords.y = new_coords.y + (direction == SUD ? speed : -speed);

    // Gestion des collisions.

    if (direction == OUEST || direction == EST) { // Axe horizontal
        int mask_x = (new_coords.x - MAP_START_PIX_X) % MAP_BLOCK_SIZE;
        int mask_y = (new_coords.y - MAP_START_PIX_Y) % MAP_BLOCK_SIZE;
        int block_x, block_y;

        // Si le mask est négatif on sort de la map
        if (mask_x < 0 || mask_y != 0) return;
        if (direction == EST)
            block_x = ((new_coords.x - mask_x + MAP_BLOCK_SIZE) - MAP_START_PIX_X) / MAP_BLOCK_SIZE;
        else
            block_x = ((new_coords.x - mask_x) - MAP_START_PIX_X) / MAP_BLOCK_SIZE;

        if (block_x >= MAP_WIDTH) return;
        block_y = (new_coords.y - MAP_START_PIX_Y) / MAP_BLOCK_SIZE;

        if (this->block_map[block_y][block_x] != NOTHING) return;
    }
    else { // Axe vertical
        int mask_x = (new_coords.x - MAP_START_PIX_X) % MAP_BLOCK_SIZE;
        int mask_y = (new_coords.y - MAP_START_PIX_Y) % MAP_BLOCK_SIZE;
        int block_x, block_y;

        // Si le mask est négatif on sort de la map
        if (mask_y < 0 || mask_x != 0) return;
        if (direction == SUD)
            block_y = ((new_coords.y - mask_y + MAP_BLOCK_SIZE) - MAP_START_PIX_Y) / MAP_BLOCK_SIZE;
        else
            block_y = ((new_coords.y - mask_y) - MAP_START_PIX_Y) / MAP_BLOCK_SIZE;

        if (block_y >= MAP_HEIGHT) return;
        block_x = (new_coords.x - MAP_START_PIX_X) / MAP_BLOCK_SIZE;

        if (this->block_map[block_y][block_x] != NOTHING) return;
    }
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

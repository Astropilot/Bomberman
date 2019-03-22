/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the game map class.
*/

#include <stdio.h>
#include <SDL2/SDL.h>

#include "core/map.h"
#include "core/utils.h"
#include "network/packets/packet_ack_bombexplode.h"

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
    this->Place_Bomb = TMap_Place_Bomb;
    this->Explose_Bomb = TMap_Explose_Bomb;
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
    this->max_players = max_clients;
    this->bombs_head = NULL;
    this->bomb_offset = 0;
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
    unsigned int i;
    int tmp_x, tmp_y;
    bomb_node_t *current_bomb = this->bombs_head;
    unsigned int current_time = SDL_GetTicks();

    if (current_time <= player->last_move_time + player->specs.move_speed)
        return;
    player->last_move_time = current_time;
    player->direction = (unsigned int)direction;
    if (direction == OUEST || direction == EST)
        new_coords.x = new_coords.x + (direction == EST ? MAP_BLOCK_SIZE : -MAP_BLOCK_SIZE);
    else
        new_coords.y = new_coords.y + (direction == SUD ? MAP_BLOCK_SIZE : -MAP_BLOCK_SIZE);
    pix_to_map((int)new_coords.x, (int)new_coords.y, &block_x, &block_y);

    // Gestion des collisions avec les blocs infranchissables.
    if (block_x < 0 || block_x >= MAP_WIDTH) return;
    if (block_y < 0 || block_y >= MAP_HEIGHT) return;
    if (this->block_map[block_y][block_x] == WALL || this->block_map[block_y][block_x] == BREAKABLE_WALL)
        return;

    // Gestion des collisions avec les autres joueurs.
    for(i = 0; i < this->max_players; i++) {
        if (this->players[i].connected == 1 && this->players[i].p_id != player_id) {
            pix_to_map((int)this->players[i].pos.x, (int)this->players[i].pos.y, &tmp_x, &tmp_y);
            if (block_y == tmp_y && block_x == tmp_x) return;
        }
    }

    // Gestion des collisions avec les bombes.
    while (current_bomb != NULL) {
        if ((int)current_bomb->bomb->bomb_pos.x == block_x && (int)current_bomb->bomb->bomb_pos.y == block_y) {
            return;
        }
        current_bomb = current_bomb->next;
    }

    player->pos.x = new_coords.x;
    player->pos.y = new_coords.y;
}

bomb_status_t TMap_Place_Bomb(TMap *this, unsigned int player_id, bomb_reason_t *reason)
{
    player_t *player = &(this->players[player_id]);
    int block_x, block_y;
    unsigned int time = SDL_GetTicks();
    bomb_t *bomb;
    bomb_node_t *current_bomb = this->bombs_head;

    if (player->specs.bombs_left <= 0) {
        *reason = NO_MORE_CAPACITY;
        return (BOMB_CANCELED);
    }
    pix_to_map((int)player->pos.x, (int)player->pos.y, &block_x, &block_y);

    while (current_bomb != NULL) {
        if (current_bomb->bomb->bomb_pos.x == (unsigned int)block_x && current_bomb->bomb->bomb_pos.y == (unsigned int)block_y) {
            *reason = ALREADY_ITEM;
            return (BOMB_CANCELED);
        }
        current_bomb = current_bomb->next;
    }

    bomb = malloc(sizeof(bomb_t));
    if (!bomb) {
        *reason = INTERNAL_ERROR;
        return (BOMB_CANCELED);
    }

    player->specs.bombs_left--;
    this->bomb_offset++;

    bomb->id = this->bomb_offset - 1;
    bomb->bomb_pos.x = (unsigned int)block_x;
    bomb->bomb_pos.y = (unsigned int)block_y;
    bomb->type = CLASSIC;
    bomb->range = player->specs.bombs_range;
    bomb->time_explode = time + 5000;
    bomb->owner_id = player_id;
    add_bomb(&(this->bombs_head), bomb);
    //add_bomb(&(player->specs.bombs_head), bomb);

    return (BOMB_POSED);
}

void TMap_Explose_Bomb(TMap *this, bomb_t *bomb, TAckBombExplodePacket *packet)
{
    player_t *player = &(this->players[bomb->owner_id]);
    unsigned int y;
    unsigned int x;
    unsigned int bomb_start_x, bomb_start_y;
    unsigned int bomb_end_x, bomb_end_y;

    player->specs.bombs_left++;
    packet->bomb = *bomb;
    //TODO: Implémenter la logique de l'explosion des bombes.

    // Supprimer les murs cassables présent dans le rayon de la bombe +
    // Remplacer par un extra (bonus/malus) si chance.
    bomb_start_x = ((int)bomb->bomb_pos.x - (int)bomb->range >= 0) ? bomb->bomb_pos.x - bomb->range : 0;
    bomb_start_y = ((int)bomb->bomb_pos.y - (int)bomb->range >= 0) ? bomb->bomb_pos.y - bomb->range : 0;
    bomb_end_x = ((int)bomb->bomb_pos.x + (int)bomb->range < MAP_WIDTH) ? bomb->bomb_pos.x + bomb->range : MAP_WIDTH - 1;
    bomb_end_y = ((int)bomb->bomb_pos.y + (int)bomb->range < MAP_HEIGHT) ? bomb->bomb_pos.y + bomb->range: MAP_HEIGHT - 1;

    packet->destroyed_count = 0;
    for (y = bomb_start_y; y <= bomb_end_y; y++)
        for (x = bomb_start_x; x <= bomb_end_x; x++)
            if (this->block_map[y][x] == BREAKABLE_WALL)
                packet->destroyed_count++;

    packet->destroyed_walls = malloc(sizeof(pos_t) * packet->destroyed_count);
    packet->extra_blocks = malloc(sizeof(object_t) * packet->destroyed_count);
    packet->destroyed_count = 0;
    packet->extra_count = 0;

    for (y = bomb_start_y; y <= bomb_end_y; y++) {
        for (x = bomb_start_x; x <= bomb_end_x; x++) {
            if (this->block_map[y][x] == BREAKABLE_WALL) {
                pos_t pos = {x, y};
                this->block_map[y][x] = NOTHING;
                if (rand_int(100) <= CHANCE_EXTRA) {
                    object_t obj = {BONUS_RANGE, {x, y}};

                    this->block_map[y][x] = BONUS_RANGE;
                    packet->extra_blocks[packet->extra_count] = obj;
                    packet->extra_count++;
                }

                packet->destroyed_walls[packet->destroyed_count] = pos;
                packet->destroyed_count++;
            }
        }
    }

    //TODO: Checker les joueurs dans le rayon et leur retirer de la vie.
}

void TMap_New_Free(TMap *this)
{
    if (this) {
        unsigned int i;
        bomb_node_t *current = this->bombs_head;
        bomb_node_t *tmp = NULL;

        while (current != NULL) {
            free(current->bomb);
            tmp = current;
            current = current->next;
            free(tmp);
        }

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

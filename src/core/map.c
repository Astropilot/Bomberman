/*******************************************************************************
* PROJECT: Bomberman
*
* AUTHORS: Yohann Martin, Aziz Hamide, Gauthier Desplanque, William Weber
*
* DATE CREATED: 01/16/2019
*
* Copyright (c) 2019 Yohann MARTIN (@Astropilot). All rights reserved.
*
* Licensed under the MIT License. See LICENSE file in the project root for full
* license information.
*******************************************************************************/

#include <stdio.h>
#include <SDL2/SDL.h>

#include "main.h"
#include "core/map.h"
#include "core/extra.h"
#include "core/player.h"
#include "core/bomb.h"
#include "core/utils.h"

static void TMap_Init(TMap *this, unsigned int max_clients);
static unsigned int TMap_Take_Extra(TMap *this, player_t *player, int x, int y);

TMap *New_TMap(unsigned int max_clients)
{
    TMap *this = malloc(sizeof(TMap));

    if(!this) return (NULL);
    TMap_Init(this, max_clients);
    this->Free = TMap_New_Free;
    return (this);
}

static void TMap_Init(TMap *this, unsigned int max_clients)
{
    if (!this) return;

    unsigned int i;
    unsigned int j;

    this->Generate = TMap_Generate;
    this->Move_Player = TMap_Move_Player;
    this->Place_Bomb = TMap_Place_Bomb;
    this->Explose_Bomb = TMap_Explose_Bomb;
    this->block_map = malloc(MAP_HEIGHT * sizeof(object_type_t*));
    if (this->block_map) {
        for (i = 0; i < MAP_HEIGHT; i++) {
            this->block_map[i] = malloc(MAP_WIDTH * sizeof(object_type_t));
            for (j = 0; j < MAP_WIDTH; j++) {
                this->block_map[i][j] = NOTHING;
            }
        }
    }
    this->players = malloc(sizeof(player_t) * max_clients);
    if (this->players) {
        for (i = 0; i < max_clients; i++) {
            this->players[i].connected = 0;
        }
    }
    this->max_players = max_clients;
    this->bombs_head = NULL;
    this->bomb_offset = 0;
}

void TMap_Generate(TMap *this)
{
    if (!this || !this->block_map) return;

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
                // Si chance d'avoir un mur cassable
                if (rand_int(100) <= CHANCE_BREAKABLE_WALL) {
                    this->block_map[y][x] = BREAKABLE_WALL;
                }
            }
        }
    }
}

static unsigned int TMap_Take_Extra(TMap *this, player_t *player, int x, int y)
{
    if (!this || !player || !this->block_map) return (0);
    if (this->block_map[y][x] == NOTHING) return (0);

    unsigned int res = do_extra_logic(player, this->block_map[y][x]);

    if (res)
        this->block_map[y][x] = NOTHING;
    return (res);
}

unsigned int TMap_Move_Player(TMap *this, unsigned int player_id, direction_t direction)
{
    if (!this || !this->block_map || !this->players) return (0);

    player_t *player = &(this->players[player_id]);
    pos_t new_coords = player->pos;
    int block_x, block_y;
    unsigned int i;
    int tmp_x, tmp_y;
    bomb_node_t *current_bomb = this->bombs_head;
    unsigned int current_time = SDL_GetTicks();

    if (current_time <= player->last_move_time + player->specs.move_speed
        ||
        player->specs.life <= 0)
        return (0);
    player->last_move_time = current_time;
    player->direction = (unsigned int)direction;
    if (direction == WEST || direction == EAST)
        new_coords.x = new_coords.x + (direction == EAST ? MAP_BLOCK_SIZE : -MAP_BLOCK_SIZE);
    else
        new_coords.y = new_coords.y + (direction == SOUTH ? MAP_BLOCK_SIZE : -MAP_BLOCK_SIZE);
    pix_to_map((int)new_coords.x, (int)new_coords.y, &block_x, &block_y);

    // Gestion des collisions avec les blocs infranchissables.
    if (block_x < 0 || block_x >= MAP_WIDTH) return (0);
    if (block_y < 0 || block_y >= MAP_HEIGHT) return (0);
    if (this->block_map[block_y][block_x] == WALL ||
        this->block_map[block_y][block_x] == BREAKABLE_WALL)
        return (0);

    // Gestion des collisions avec les autres joueurs.
    for(i = 0; i < this->max_players; i++) {
        if (this->players[i].connected == 1 && this->players[i].p_id != player_id) {
            pix_to_map((int)this->players[i].pos.x, (int)this->players[i].pos.y, &tmp_x, &tmp_y);
            if (block_y == tmp_y && block_x == tmp_x) return (0);
        }
    }

    // Gestion des collisions avec les bombes.
    while (current_bomb != NULL) {
        if ((int)current_bomb->bomb->bomb_pos.x == block_x &&
            (int)current_bomb->bomb->bomb_pos.y == block_y) {
            return (0);
        }
        current_bomb = current_bomb->next;
    }

    player->pos.x = new_coords.x;
    player->pos.y = new_coords.y;

    return TMap_Take_Extra(this, player, block_x, block_y);
}

bomb_status_t TMap_Place_Bomb(TMap *this, unsigned int player_id, bomb_reason_t *reason)
{
    if (!this || !reason || !this->block_map || !this->players) {
        if (reason)
            *reason = INTERNAL_ERROR;
        return (BOMB_CANCELED);
    }

    player_t *player = &(this->players[player_id]);
    int block_x, block_y;
    unsigned int time = SDL_GetTicks();
    bomb_t *bomb;
    bomb_node_t *current_bomb = this->bombs_head;

    if (player->specs.bombs_left <= 0 || player->specs.life <= 0) {
        *reason = NO_MORE_CAPACITY;
        return (BOMB_CANCELED);
    }
    pix_to_map((int)player->pos.x, (int)player->pos.y, &block_x, &block_y);

    while (current_bomb != NULL) {
        if (current_bomb->bomb->bomb_pos.x == (unsigned int)block_x &&
            current_bomb->bomb->bomb_pos.y == (unsigned int)block_y) {
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
    bomb->time_explode = time + rand_range_int(2000, 5000);
    bomb->owner_id = player_id;
    add_bomb(&(this->bombs_head), bomb);

    return (BOMB_POSED);
}

void TMap_Explose_Bomb(TMap *this, bomb_t *bomb, TServer *server)
{
    if (!this || !this->block_map || !this->players || !bomb || !server)
        return;

    do_bomb_logic(this, bomb, server);
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
        if (this->block_map) {
            for (i = 0; i < MAP_HEIGHT; i++) {
                free(this->block_map[i]);
            }
            free(this->block_map);
            this->block_map = NULL;
        }
        free(this->players);
        this->players = NULL;
    }
    free(this);
}

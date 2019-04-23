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

/**
 * @file core/map.h
 * @brief Header file of the Map class.
 *
 * This class allows you to create new Bomberman Map and manipulate it.
 *
 */

#ifndef CORE_MAP_H_
#define CORE_MAP_H_

#include "core/player.h"
#include "core/utils.h"
#include "core/bomb.h"
#include "network/network.h"

typedef struct minion_t minion_t;

/**
 * @brief Constants of the static blocks on the map.
 *
 * object_type_t is a series of predefined constants for the different
 * static blocks on the map.
 */
typedef enum object_type_t {
    NOTHING,                    /*!< No block or item. */
    WALL,                       /*!< An indestructible wall. */
    BREAKABLE_WALL,             /*!< A wall that can be destroyed by bombs. */
    BONUS_RANGE,                /*!< A bonus for bomb range. */
    MALUS_RANGE,                /*!< A malus for bomb range. */
    BONUS_CAPACITY,             /*!< A bonus for bomb capacity. */
    MALUS_CAPACITY,             /*!< A malus for bomb capacity. */
    BONUS_SPEED,                /*!< A bonus for player speed. */
    MALUS_SPEED                 /*!< A malus for player speed. */
} object_type_t ;

/**
 * @brief structure representing a map object.
 *
 * object_t is an structure representing a map object.
 */
typedef struct object_t {

    object_type_t type;         /*!< The type (object_type_t) of object. */
    pos_t pos;                  /*!< The position of the object on the map. */

} object_t ;

/**
 * @brief An class representing a Bomberman Map.
 *
 * TMap is a class for creating and managing a Bomberman Map.
 */
typedef struct TMap {

    void(*Generate)(struct TMap*);                                          /*!< Method for generate a new map. */

    unsigned int(*Move_Player)(struct TMap*, unsigned int, direction_t);    /*!< Method for move a specific player in a given direction. */

    bomb_status_t(*Place_Bomb)(struct TMap*, unsigned int, bomb_reason_t*); /*!< Method for place a bomb by a player. */

    void(*Explose_Bomb)(struct TMap*, bomb_t*, TServer*);                   /*!< Method for call the bomb logic to explode. */

    void(*Free)(struct TMap*);                                              /*!< Free (ressources) method. */

    object_type_t **block_map;  /*!< The 2D array representing the Map. */
    unsigned int max_players;   /*!< The maximum of player that can be on the map. */
    player_t *players;          /*!< The list of players. */
    minion_t *minion;           /*!< The minion entity. */
    bomb_node_t *bombs_head;    /*!< The list of bombs that need to explode soon. */
    unsigned int bomb_offset;   /*!< A self-incrementing integer representing the next ID of a new bomb. */

} TMap ;

/**
 * @brief The constructor for create a TMap object.
 *
 * @param max_clients The maximum number of players that can be on the map.
 * @return A memory allocated object of the map.
 */
TMap *New_TMap(unsigned int max_clients);

/**
 * @brief Method for generate a random map.
 *
 * @param this A pointer to the map object.
 *
 * You do not have to call this method directly. You must use the
 * Generate method of the TMap structure like this:
 * my_map->Generate(my_map);
 */
void TMap_Generate(TMap *this);

/**
 * @brief Method for moving a player on the map with a given direction.
 *
 * @param this A pointer to the map object.
 * @param player_id The ID of the player to move.
 * @param direction The direction where the player want to go.
 * @return Returns 1 if the player picks up an extra while moving, 0 if not.
 *
 * You do not have to call this method directly. You must use the
 * Move_Player method of the TMap structure like this:
 * my_map->Move_Player(my_map, 0, NORTH);
 */
unsigned int TMap_Move_Player(TMap *this, unsigned int player_id, direction_t direction);

/**
 * @brief Method for drop a bomb at the player position.
 *
 * @param this A pointer to the map object.
 * @param player_id The ID of the player who want to drop a bomb.
 * @param reason The reason given if the drop fail.
 * @return Return the status of the player request.
 *
 * You do not have to call this method directly. You must use the
 * Place_Bomb method of the TMap structure like this:
 * my_map->Place_Bomb(my_map, 0, &my_reason);
 */
bomb_status_t TMap_Place_Bomb(TMap *this, unsigned int player_id, bomb_reason_t *reason);

/**
 * @brief Method for explode a specific bomb.
 *
 * @param this A pointer to the map object.
 * @param bomb The bomb that need to explode.
 * @param server The network server in order to send additional packets if necessary.
 *
 * You do not have to call this method directly. You must use the
 * Explose_Bomb method of the TMap structure like this:
 * my_map->Explose_Bomb(my_map, my_bomb, my_server);
 */
void TMap_Explose_Bomb(TMap *this, bomb_t *bomb, TServer *server);

/**
 * @brief Method to free all ressources take by the map.
 *
 * @param this A pointer to the map object to free.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TMap structure like this:
 * my_map->Free(my_map);
 */
void TMap_New_Free(TMap *this);

#endif

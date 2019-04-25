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
 * @file core/bomb.h
 * @brief Header file of the bombs logic.
 *
 * All methods for bombs logic are here.
 *
 */

#ifndef CORE_BOMB_H_
#define CORE_BOMB_H_

#include "core/utils.h"

typedef struct TMap TMap;
typedef struct TGameServer TGameServer;

/**
 * @brief Constants of the possible status when a player try to drop a bomb.
 *
 * bomb_status_t is a series of predefined constants for the different
 * possible status when a player try to drop a bomb.
 */
typedef enum bomb_status_t {
    BOMB_POSED,                 /*!< The bomb has been drop. */
    BOMB_CANCELED               /*!< The bomb cannot be dropped. */
} bomb_status_t ;

/**
 * @brief Constants of the possible reason when the drop of a bomb have failed.
 *
 * bomb_reason_t is a series of predefined constants for the different
 * possible reason when the drop of a bomb have failed
 */
typedef enum bomb_reason_t {
    ALREADY_ITEM,               /*!< A bomb or extra is already here. */
    NO_MORE_CAPACITY,           /*!< The player has no more bombs left. */
    INTERNAL_ERROR,             /*!< An internal error occured. */
    NO_REASON                   /*!< Reason given if bomb has been drop. */
} bomb_reason_t ;

/**
 * @brief Constants of the types of bombs available.
 *
 * TButton_State is a series of predefined constants for the different
 * types of bombs available.
 */
typedef enum bomb_type_t {
    CLASSIC                     /*!< The classic bomb. */
} bomb_type_t ;

/**
 * @brief structure representing a bomb.
 *
 * bomb_t is an object representing a bomb.
 */
typedef struct bomb_t {

    unsigned int id;            /*!< The unique ID of the bomb. */
    pos_t bomb_pos;             /*!< The position of the bomb. */
    unsigned int type;          /*!< The type (bomb_type_t) of the bomb. */
    unsigned int range;         /*!< The range of the explosion. */
    unsigned int time_explode;  /*!< The time when the bomb will explode. */
    unsigned int owner_id;      /*!< The owner ID of the bomb. */

} bomb_t ;

/**
 * @brief A linked list node for bombs.
 *
 * bomb_node_t is an linked list node for stock bombs objects.
 */
typedef struct bomb_node_t {

    bomb_t *bomb;               /*!< The bomb object. */
    struct bomb_node_t *next;   /*!< A pointer to the next bomb_node_t. */

} bomb_node_t ;

/**
 * @brief Method for adding a bomb to a bomb linked list.
 *
 * @param bombs_head A pointer to the linked list.
 * @param bomb The bomb to add.
 */
void add_bomb(bomb_node_t **bombs_head, bomb_t *bomb);

/**
 * @brief Method for deleting a bomb from a bomb linked list.
 *
 * @param bombs_head A pointer to the linked list.
 * @param bomb The bomb to delete.
 */
void remove_bomb(bomb_node_t **bombs_head, bomb_t *bomb);

/**
 * @brief Call the logic function corresponding to the bomb type.
 *
 * @param map A pointer to the game map.
 * @param bomb A pointer to the bomb.
 * @param gserver A pointer to the server instance.
 */
void do_bomb_logic(TMap *map, bomb_t *bomb, TGameServer *gserver);

#endif

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
 * @file core/extra.h
 * @brief Header file of the extras logic.
 *
 * All methods for extras logic are here.
 *
 */

#ifndef CORE_EXTRA_H_
#define CORE_EXTRA_H_

#include "core/map.h"

/**
 * @fn unsigned int do_extra_logic(player_t *player, object_type_t extra_type)
 * @brief Function that apply an extra to the player specs.
 *
 * @param player A pointer to the player who take the extra.
 * @param extra_type The type of extra the player has take.
 * @return Return 1 or 0 if the extra has been successfully applied.
 */
unsigned int do_extra_logic(player_t *player, object_type_t extra_type);

/**
 * @fn char *extra_to_resource(object_type_t extra_type)
 * @brief Function that give the resource path according to the extra_type given.
 *
 * @param extra_type The type of extra whose path to the resource is desired.
 * @return Return the path of the resource.
 */
char *extra_to_resource(object_type_t extra_type);

#endif

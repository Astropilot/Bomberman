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
 * @file utils.h
 * @brief Header file of some internal utils of Bomberman.
 *
 * This file have some utils for internal purpose in Bomberman.
 *
 */

#ifndef CORE_UTILS_H_
#define CORE_UTILS_H_

/**
 * @brief structure representing a 2D position.
 *
 * pos_t is a structure representing a 2D position.
 */
typedef struct pos_t {

    unsigned int x;         /*!< The position on the abscissa axis. */
    unsigned int y;         /*!< The position on the y-axis. */

} pos_t ;

/**
 * @fn int rand_int(int max)
 * @brief Return a random integer between 0 and a max given.
 *
 * @param max The maximum value.
 * @return A random integer.
 */
int rand_int(int max);

/**
 * @fn int rand_range_int(int min, int max)
 * @brief Return a random integer between a min and a max given.
 *
 * @param min The minimum value.
 * @param max The maximum value.
 * @return A random integer.
 */
int rand_range_int(int min, int max);

/**
 * @fn void map_to_pix(int x0, int y0, int *x1, int *y1)
 * @brief Convert a map position into a pixel position for the client side.
 *
 * @param x0 The x-axis on the map.
 * @param y0 The y-axis on the map.
 * @param x1 A pointer to the x-axis in pixel.
 * @param y1 A pointer to the y-axis in pixel.
 */
void map_to_pix(int x0, int y0, int *x1, int *y1);

/**
 * @fn void pix_to_map(int x0, int y0, int *x1, int *y1)
 * @brief Convert a pixel position into a map position for the server side.
 *
 * @param x0 The x-axis in pixel.
 * @param y0 The y-axis in pixel.
 * @param x1 A pointer to the x-axis on the map.
 * @param y1 A pointer to the y-axis on the map.
 */
void pix_to_map(int x0, int y0, int *x1, int *y1);

#endif

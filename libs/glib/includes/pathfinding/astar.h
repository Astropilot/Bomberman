/*******************************************************************************
* PROJECT: gLib
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
 * @file astar.h
 * @brief Header file of the A* algorithm.
 */

#ifndef GLIB_ASTAR_H_
#define GLIB_ASTAR_H_

#include "pathfinding/graph.h"

int astar_search(graph_t *graph, int(*node_cost)(int, int), vertice_t *start, vertice_t *goal);

#endif

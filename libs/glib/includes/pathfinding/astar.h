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
 * @file pathfinding/astar.h
 * @brief Header file of the A* algorithm.
 *
 * The A* algorithm allows you to search for a shorter path in a graph.
 *
 */

#ifndef GLIB_ASTAR_H_
#define GLIB_ASTAR_H_

#include "pathfinding/graph.h"

/**
 * @brief Launches a search for a shorter path and returns if a path has been found or not.
 *
 * @param graph The graph to navigate in.
 * @param node_cost A function that for a node with coordinates (x,y) returns
 * the cost of passing over this node. A return of -1 means that this node is impassable.
 * @param start The starting node.
 * @param goal The node to reach.
 * @return Returns a boolean indicating whether a path has been found.
 * The path can be traced from the arrival node thanks to the predecessors..
 */
int astar_search(graph_t *graph, int(*node_cost)(int, int), vertice_t *start, vertice_t *goal);

#endif

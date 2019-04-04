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
 * @file graph.h
 * @brief Header file of the graph component of gLib.
 *
 * This file provides all the functions necessary for the manipulation
 * of graphs representing a 2-dimensional map.
 *
 */

#ifndef GLIB_GRAPH_H_
#define GLIB_GRAPH_H_

/**
 * @brief Representation of a node of a graph.
 *
 * vertice_t is a representation of a node of a graph.
 */
typedef struct vertice_t {
    unsigned int x;                      /*!< The x-axis position of the node. */
    unsigned int y;                     /*!< The y-axis position of the node. */
    int cost;                           /*!< Internal cost for path finding algorithms. */
    int heuristic;                      /*!< Internal heuristic for path finding algorithms. */
    struct vertice_t *predecessor;      /*!< Predecessor in case of a path finding result. */
} vertice_t ;

/**
 * @brief Representation of an adjacency list.
 *
 * adjacency_list_node_t is a representation of an adjacency list.
 */
typedef struct adjacency_list_node_t {

    vertice_t *vertice;                 /*!< The node. */
    struct adjacency_list_node_t *next; /*!< A pointer to the next node. */

} adjacency_list_node_t ;

/**
 * @brief Representation of an oriented or unoriented graph.
 *
 * graph_t is a representation of an oriented or unoriented graph.
 */
typedef struct graph_t {

    unsigned int count_vertices;                /*!< The number of nodes. */
    unsigned int map_width;                     /*!< The width of the 2D map. */
    unsigned int map_height;                    /*!< The height of the 2D map. */
    adjacency_list_node_t **adjacency_list;     /*!< The adjacency list for edges. */
    vertice_t ***vertices;                      /*!< All the nodes in the graph. */

} graph_t ;

/**
 * @fn vertice_t *new_vertice(unsigned int x, unsigned int y)
 * @brief Function to create a new graph node.
 *
 * @param x The position on the x-axis.
 * @param y The position on the y-axis.
 * @return Return a new node or NULL if the creation failed.
 */
vertice_t *new_vertice(unsigned int x, unsigned int y);

/**
 * @fn adjacency_list_node_t *new_adjacency_node(vertice_t *vertice)
 * @brief Function to create a new node of adjacency list.
 *
 * @param vertice The node on which its neighbors will be added.
 * @return Return a new adjacency list or NULL if the creation failed.
 */
adjacency_list_node_t *new_adjacency_node(vertice_t *vertice);

/**
 * @fn graph_t *create_graph(unsigned int width, unsigned int height)
 * @brief Function to create a new graph from a 2D map.
 *
 * @param width The width of the 2D map.
 * @param height The height of the 2D map.
 * @return Return a new graph or NULL if the creation failed.
 */
graph_t *create_graph(unsigned int width, unsigned int height);

/**
 * @fn void init_vertices(graph_t *graph)
 * @brief Create all node corresponding to a 2D map and add the edges.
 *
 * @param graph The graph to initialize.
 */
void init_vertices(graph_t *graph);

/**
 * @fn void add_edge(graph_t *graph, vertice_t *src, vertice_t *dest)
 * @brief Add a edge between two node in a graph. In the case of a
 * non-oriented graph, remember to call this function with the nodes in the other direction.
 *
 * @param graph The graph.
 * @param src The source node.
 * @param dest The destination node.
 */
void add_edge(graph_t *graph, vertice_t *src, vertice_t *dest);

/**
 * @fn adjacency_list_node_t *get_neighbors(graph_t *graph, vertice_t *vertice)
 * @brief Return all the neighbors of a node.
 *
 * @param graph The graph.
 * @param vertice The node to which we want the neighbors.
 * @return Return a linked list of the neighbors.
 */
adjacency_list_node_t *get_neighbors(graph_t *graph, vertice_t *vertice);

/**
 * @fn void free_graph(graph_t *graph)
 * @brief Free the resources of a graph.
 *
 * @param graph The graph.
 */
void free_graph(graph_t *graph);

#endif

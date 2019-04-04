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
 * @brief Header file of the graph component of GLib.
 */

#ifndef GLIB_GRAPH_H_
#define GLIB_GRAPH_H_

typedef struct vertice_t {
    unsigned int x;
    unsigned int y;
    unsigned int passable;
    int cost;
    int heuristic;
    struct vertice_t *predecessor;
} vertice_t ;

typedef struct adjacency_list_node_t {

    vertice_t *vertice;
    struct adjacency_list_node_t *next;

} adjacency_list_node_t ;

typedef struct graph_t {

    unsigned int vertices;
    unsigned int map_width;
    unsigned int map_height;
    adjacency_list_node_t **adjacency_list;

} graph_t ;

vertice_t *new_vertice(unsigned int x, unsigned int y, unsigned int passable);
adjacency_list_node_t *new_adjacency_node(vertice_t *vertice);
graph_t *create_graph(unsigned int width, unsigned int height);
void add_edge(graph_t *graph, vertice_t *src, vertice_t *dest);
adjacency_list_node_t *get_neighbors(graph_t *graph, vertice_t *vertice);
void free_graph(graph_t *graph);

#endif

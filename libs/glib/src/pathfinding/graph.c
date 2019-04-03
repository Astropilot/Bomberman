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

#include <stdlib.h>

#include "pathfinding/graph.h"

adjacency_list_node_t *new_adjacency_node(vertice_t *vertice)
{
    adjacency_list_node_t *node = malloc(sizeof(adjacency_list_node_t));

    if (!node) return (NULL);
    node->vertice = vertice;
    node->next = NULL;
    return (node);
}

graph_t *create_graph(unsigned int width, unsigned int height)
{
    graph_t *graph = malloc(sizeof(graph_t));
    unsigned int i;

    if (!graph) return (NULL);
    graph->vertices = width * height;
    graph->map_width = width;
    graph->map_height = height;

    graph->adjacency_list = malloc(graph->vertices * sizeof(adjacency_list_node_t));
    if (!graph->adjacency_list) {
        free(graph);
        return (NULL);
    }
    for (i = 0; i < graph->vertices; i++)
        graph->adjacency_list[i] = NULL;

    return (graph);
}

void add_edge(graph_t *graph, vertice_t *src, vertice_t *dest)
{
    if (!graph) return;

    adjacency_list_node_t *node_dest = new_adjacency_node(dest);
    unsigned int src_i = (src->y * graph->map_width) + src->x;

    if (!node_dest) {
        free(node_dest);
        return;
    }
    node_dest->next = graph->adjacency_list[src_i];
    graph->adjacency_list[src_i] = node_dest;
}

adjacency_list_node_t *get_neighbors(graph_t *graph, vertice_t *vertice)
{
    if (!graph) return (NULL);

    unsigned int verticle_i = (vertice->y * graph->map_width) + vertice->x;

    return (graph->adjacency_list[verticle_i]);
}

void free_graph(graph_t *graph)
{
    unsigned int i;
    adjacency_list_node_t *current;
    adjacency_list_node_t *next;

    if (graph) {
        for (i = 0; i < graph->vertices; i++) {
            current = graph->adjacency_list[i];

            while (current) {
                next = current->next;
                free(current);
                current = next;
            }
        }
        free(graph->adjacency_list);
    }
    free(graph);
}

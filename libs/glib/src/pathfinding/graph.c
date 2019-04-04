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

vertice_t *new_vertice(unsigned int x, unsigned int y)
{
    vertice_t *vertice = malloc(sizeof(vertice_t));

    if (!vertice) return (NULL);

    vertice->x = x;
    vertice->y = y;
    vertice->cost = 0;
    vertice->heuristic = 0;
    vertice->predecessor = NULL;
    return (vertice);
}

adjacency_list_node_t *new_adjacency_node(vertice_t *vertice)
{
    if (!vertice) return (NULL);

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
    unsigned int j;

    if (!graph) return (NULL);
    graph->count_vertices = width * height;
    graph->map_width = width;
    graph->map_height = height;
    graph->vertices = NULL;

    graph->adjacency_list = malloc(graph->count_vertices * sizeof(adjacency_list_node_t));
    graph->vertices = malloc(height * sizeof(vertice_t**));
    if (!graph->adjacency_list || !graph->vertices) {
        free_graph(graph);
        return (NULL);
    }
    for (i = 0; i < graph->count_vertices; i++)
        graph->adjacency_list[i] = NULL;

    for (i = 0; i < height; i++) {
        graph->vertices[i] = malloc(width * sizeof(vertice_t*));
        if (!graph->vertices[i]) {
            free_graph(graph);
            return (NULL);
        }
        for (j = 0; j < width; j++) {
            graph->vertices[i][j] = NULL;
        }
    }

    return (graph);
}

void init_vertices(graph_t *graph)
{
    if (!graph) return;

    int i;
    int j;
    int map_height = (int)graph->map_height;
    int map_width = (int)graph->map_width;

    for (i = 0; i < map_height; i++) {
        for (j = 0; j < map_width; j++) {
            vertice_t *vert = new_vertice(j, i);

            graph->vertices[i][j] = vert;
        }
    }

    for (i = 0; i < map_height; i++) {
        for (j = 0; j < map_width; j++) {
            if (i - 1 >= 0)
                add_edge(graph, graph->vertices[i][j], graph->vertices[i-1][j]);
            if (i + 1 < map_height)
                add_edge(graph, graph->vertices[i][j], graph->vertices[i+1][j]);
            if (j - 1 >= 0)
                add_edge(graph, graph->vertices[i][j], graph->vertices[i][j-1]);
            if (j + 1 < map_width)
                add_edge(graph, graph->vertices[i][j], graph->vertices[i][j+1]);
        }
    }
}

void add_edge(graph_t *graph, vertice_t *src, vertice_t *dest)
{
    if (!graph || !src || !dest) return;

    adjacency_list_node_t *node_dest = new_adjacency_node(dest);
    unsigned int src_i = (src->y * graph->map_width) + src->x;

    if (!node_dest) return;
    node_dest->next = graph->adjacency_list[src_i];
    graph->adjacency_list[src_i] = node_dest;
}

adjacency_list_node_t *get_neighbors(graph_t *graph, vertice_t *vertice)
{
    if (!graph || !vertice) return (NULL);

    unsigned int verticle_i = (vertice->y * graph->map_width) + vertice->x;

    return (graph->adjacency_list[verticle_i]);
}

void free_graph(graph_t *graph)
{
    unsigned int i;
    unsigned int j;
    adjacency_list_node_t *current;
    adjacency_list_node_t *next;

    if (graph) {
        if (graph->adjacency_list) {
            for (i = 0; i < graph->count_vertices; i++) {
                current = graph->adjacency_list[i];

                while (current) {
                    next = current->next;
                    free(current);
                    current = next;
                }
            }
        }
        free(graph->adjacency_list);
        graph->adjacency_list = NULL;
        if (graph->vertices) {
            for (i = 0; i < graph->map_height; i++) {
                if (graph->vertices[i]) {
                    for (j = 0; j < graph->map_width; j++) {
                        free(graph->vertices[i][j]);
                    }
                }
                free(graph->vertices[i]);
            }
        }
        free(graph->vertices);
        graph->vertices = NULL;
    }
    free(graph);
}

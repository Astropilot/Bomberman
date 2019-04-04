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

#include "pathfinding/astar.h"
#include "pathfinding/queue.h"
#include "pathfinding/priority_queue.h"

int compare_node(void *n1, void *n2)
{
    vertice_t *node1 = (vertice_t*)n1;
    vertice_t *node2 = (vertice_t*)n2;

    if (node1->heuristic < node2->heuristic)
        return (1);
    else if (node1->heuristic == node2->heuristic)
        return (0);
    return (-1);
}

int heuristic_manhattan(vertice_t *src, vertice_t *dest)
{
    if (!src || !dest) return (-1);
    return ( abs(src->x - dest->x) + abs(src->y - dest->y) );
}

int astar_search(graph_t *graph, vertice_t *start, vertice_t *goal)
{
    if (!graph || !start || !goal) return (0);

    queue_t *closed_list = create_queue();
    priority_queue_t *open_list = create_priority_queue(compare_node);

    if (!closed_list || !open_list) {
        free_queue(closed_list);
        free_priority_queue(open_list);
        return (0);
    }

    push_priority_queue(open_list, (void*)start);
    while (!is_priority_queue_empty(open_list)) {
        vertice_t *u = (vertice_t*)pop_priority_queue(open_list);
        adjacency_list_node_t *neighbor;

        if (u->x == goal->x && u->y == goal->y) {
            free_queue(closed_list);
            free_priority_queue(open_list);
            return (1);
        }
        neighbor = get_neighbors(graph, u);
        while (neighbor) {
            vertice_t *v = (vertice_t*)neighbor->vertice;

            if (v->passable && !is_present_in_queue(closed_list, (void*)v) &&
                !is_present_in_priority_queue(open_list, (void*)v)) {
                    v->cost++;
                    v->heuristic = v->cost + heuristic_manhattan(v, goal);
                    v->predecessor = u;
                    push_priority_queue(open_list, v);
                }
            neighbor = neighbor->next;
        }
        push_queue(closed_list, u);
    }

    free_queue(closed_list);
    free_priority_queue(open_list);
    return (0);
}

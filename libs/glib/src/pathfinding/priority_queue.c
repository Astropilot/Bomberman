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

#include "pathfinding/priority_queue.h"

priority_queue_t *create_priority_queue(int(*compare)(void*, void*))
{
    priority_queue_t *pqueue = malloc(sizeof(priority_queue_t));

    if (!pqueue || !compare) {
        if (pqueue) free(pqueue);
        return (NULL);
    }
    pqueue->compare = compare;
    pqueue->size = 0;
    pqueue->head = NULL;
    return (pqueue);
}

unsigned int push_priority_queue(priority_queue_t *pqueue, void *data)
{
    if (!pqueue || !data) return (0);

    priority_queue_node_t *item = malloc(sizeof(priority_queue_node_t));

    if (!item) return (0);

    item->data = data;
    item->next = NULL;

    if (pqueue->size == 0)
        pqueue->head = item;
    else {
        if (pqueue->compare(pqueue->head->data, data) < 0) {
            item->next = pqueue->head;
            pqueue->head = item;
        } else {
            priority_queue_node_t *current = pqueue->head;

            while (current->next && pqueue->compare(current->next->data, data) < 0)
                current = current->next;

            item->next = current->next;
            current->next = item;
        }
    }

    pqueue->size++;
    return (1);
}

void *pop_priority_queue(priority_queue_t *pqueue)
{
    priority_queue_node_t *item;
    void *data;

    if (is_priority_queue_empty(pqueue)) return (NULL);
    item = pqueue->head;
    pqueue->head = item->next;
    pqueue->size--;
    data = item->data;
    free(item);

    return (data);
}

unsigned int is_present_in_priority_queue(priority_queue_t *pqueue, void *data)
{
    if (!pqueue || !data || pqueue->size == 0) return (0);

    priority_queue_node_t *current = pqueue->head;

    while (current) {
        if (current->data == data)
            return (1);
        current = current->next;
    }
    return (0);
}

unsigned int is_priority_queue_empty(priority_queue_t *pqueue)
{
    if (!pqueue) return (0);

    return (pqueue->size == 0);
}

void free_priority_queue(priority_queue_t *pqueue)
{
    while (!is_priority_queue_empty(pqueue)) {
        pop_priority_queue(pqueue);
    }
    free(pqueue);
}

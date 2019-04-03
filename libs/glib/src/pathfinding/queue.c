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

#include "pathfinding/queue.h"

queue_t *create_queue(void)
{
    queue_t *queue = malloc(sizeof(queue_t));

    if (!queue) return (NULL);
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;
    return (queue);
}

unsigned int push_queue(queue_t *queue, void *data)
{
    if (!queue || !data) return (0);

    queue_node_t *item = malloc(sizeof(queue_node_t));
    if (!item) return (0);

    item->data = data;
    item->prev = NULL;
    if (queue->size == 0) {
        queue->head = item;
        queue->tail = item;
    } else {
        queue->tail->prev = item;
        queue->tail = item;
    }
    queue->size++;
    return (1);
}

void *pop_queue(queue_t *queue)
{
    queue_node_t *item;
    void *data;

    if (is_queue_empty(queue)) return (NULL);
    item = queue->head;
    queue->head = item->prev;
    queue->size--;
    data = item->data;
    free(item);

    return (data);
}

unsigned int is_present_in_queue(queue_t *queue, void *data)
{
    if (!queue || !data || queue->size == 0) return (0);

    queue_node_t *current = queue->head;

    while (current) {
        if (current->data == data)
            return (1);
        current = current->prev;
    }
    return (0);
}

unsigned int is_queue_empty(queue_t *queue)
{
    if (!queue) return (0);

    return (queue->size == 0);
}

void free_queue(queue_t *queue)
{
    while (!is_queue_empty(queue)) {
        pop_queue(queue);
    }
    free(queue);
}

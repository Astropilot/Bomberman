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
 * @file queue.h
 * @brief Header file of the queue data structure.
 */

#ifndef GLIB_QUEUE_H_
#define GLIB_QUEUE_H_

typedef struct queue_node_t {

    void *data;
    struct queue_node_t *prev;

} queue_node_t ;

typedef struct queue_t {

    queue_node_t *head;
    queue_node_t *tail;
    unsigned int size;

} queue_t ;

queue_t *create_queue(void);
unsigned int push_queue(queue_t *queue, void *data);
void *pop_queue(queue_t *queue);
unsigned int is_present_in_queue(queue_t *queue, void *data);
unsigned int is_queue_empty(queue_t *queue);
void free_queue(queue_t *queue);

#endif

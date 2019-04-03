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
 * @brief Header file of the priority queue data structure.
 */

#ifndef GLIB_PRIORITY_QUEUE_H_
#define GLIB_PRIORITY_QUEUE_H_

typedef struct priority_queue_node_t {

    void *data;
    struct priority_queue_node_t *next;

} priority_queue_node_t ;

typedef struct priority_queue_t {

    int(*compare)(void*, void*);
    priority_queue_node_t *head;
    unsigned int size;

} priority_queue_t ;

priority_queue_t *create_priority_queue(int(*compare)(void*, void*));
unsigned int push_priority_queue(priority_queue_t *pqueue, void *data);
void *pop_priority_queue(priority_queue_t *pqueue);
unsigned int is_present_in_priority_queue(priority_queue_t *pqueue, void *data);
unsigned int is_priority_queue_empty(priority_queue_t *pqueue);
void free_priority_queue(priority_queue_t *pqueue);

#endif

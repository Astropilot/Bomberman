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
 * @file pathfinding/queue.h
 * @brief Header file of the queue data structure.
 */

#ifndef GLIB_QUEUE_H_
#define GLIB_QUEUE_H_

/**
 * @brief Represents a node in a queue.
 *
 * queue_node_t represents a node in a queue.
 */
typedef struct queue_node_t {

    void *data;                     /*!< The data in the queue. */
    struct queue_node_t *prev;      /*!< The next element in the queue. */

} queue_node_t ;

/**
 * @brief Represents a queue.
 *
 * priority_queue_t represents a queue.
 */
typedef struct queue_t {

    queue_node_t *head;             /*!< The head of the queue. */
    queue_node_t *tail;             /*!< The tail of the queue. */
    unsigned int size;              /*!< The size of the queue. */

} queue_t ;

/**
 * @brief Function to create a new queue.
 *
 * @return Return a new queue or NULL if the creation failed.
 */
queue_t *create_queue(void);

/**
 * @brief Function to push a new element in a queue.
 *
 * @param queue The queue.
 * @param data The element to add.
 * @return Returns 1 if the addition was successful, 0 if not.
 */
unsigned int push_queue(queue_t *queue, void *data);

/**
 * @brief Function to pop a element of a queue.
 *
 * @param queue The queue.
 * @return Returns the first element added.
 */
void *pop_queue(queue_t *queue);

/**
 * @brief Function to check if a element is in a queue.
 *
 * @param queue The queue.
 * @param data The element whose presence is to be checked.
 * @return Returns 1 if the element is present, 0 if not.
 */
unsigned int is_present_in_queue(queue_t *queue, void *data);

/**
 * @brief Function to check if queue is empty.
 *
 * @param queue The queue.
 * @return Returns 1 if the queue is empty, 0 if not.
 */
unsigned int is_queue_empty(queue_t *queue);

/**
 * @brief Function to free up resources in a queue.
 *
 * @param queue The queue.
 */
void free_queue(queue_t *queue);

#endif

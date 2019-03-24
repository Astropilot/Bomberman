/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the bomb class.
*/

#include <stdlib.h>
#include <stdio.h>

#include "core/bomb.h"
#include "main.h"
#include "core/utils.h"

void add_bomb(bomb_node_t **bombs_head, bomb_t *bomb)
{
    if (!bomb)
        return;
    if (!*(bombs_head)) {
        bomb_node_t *bomb_node = malloc(sizeof(bomb_node_t));

        bomb_node->bomb = bomb;
        bomb_node->next = NULL;
        *(bombs_head) = bomb_node;
    } else {
        bomb_node_t *current = *(bombs_head);

        while (current->next != NULL)
            current = current->next;
        current->next = malloc(sizeof(bomb_node_t));
        current->next->bomb = bomb;
        current->next->next = NULL;
    }
}

void remove_bomb(bomb_node_t **bombs_head, bomb_t *bomb)
{
    if (!*(bombs_head) || !bomb)
        return;

    bomb_node_t *current = *bombs_head;
    bomb_node_t *previous = NULL;

    while (current != NULL) {
        if (current->bomb == bomb) {
            if (!previous)
                *bombs_head = current->next;
            else
                previous->next = current->next;
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

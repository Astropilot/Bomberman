/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the game map class.
*/

#ifndef CORE_UTILS_H_
#define CORE_UTILS_H_

#include <stdlib.h>

typedef struct pos_size_s {

    unsigned int x;
    unsigned int y;

} pos_t ;

int rand_int(int max);
void map_to_pix(unsigned int x0, unsigned int y0, unsigned int *x1, unsigned int *y1);
void pix_to_map(unsigned int x0, unsigned int y0, unsigned int *x1, unsigned int *y1);

#endif
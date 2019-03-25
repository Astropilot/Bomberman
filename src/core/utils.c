/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the utils class.
*/

#include <stdlib.h>
#include <time.h>

#include "core/utils.h"
#include "main.h"

static int rand_init = 0;

int rand_int(int max)
{
    int div = RAND_MAX/(max+1);
    int rand_int;

    if (!rand_init) {
        srand(time(NULL));
        rand_init = 1;
    }
    do {
        rand_int = rand() / div;
    } while (rand_int > max);
    return (rand_int);
}

int rand_range_int(int min, int max)
{
    if (!rand_init) {
        srand(time(NULL));
        rand_init = 1;
    }
    return ( rand() % (max + 1 - min) ) + min;
}

void map_to_pix(int x0, int y0, int *x1, int *y1)
{
    *x1 = MAP_START_PIX_X + (x0 * MAP_BLOCK_SIZE);
    *y1 = MAP_START_PIX_Y + (y0 * MAP_BLOCK_SIZE);
}

void pix_to_map(int x0, int y0, int *x1, int *y1)
{
    *x1 = (x0 - MAP_START_PIX_X) / MAP_BLOCK_SIZE;
    *y1 = (y0 - MAP_START_PIX_Y) / MAP_BLOCK_SIZE;
}

#include "core/utils.h"
#include "main.h"

int rand_int(int max) {
    int div = RAND_MAX/(max+1);
    int rand_int;

    do {
        rand_int = rand() / div;
    } while (rand_int > max);
    return (rand_int);
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

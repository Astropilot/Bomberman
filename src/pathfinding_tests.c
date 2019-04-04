#include <stdio.h>
#include <stdlib.h>

#include "pathfinding/graph.h"
#include "pathfinding/astar.h"

#define MAP_WIDTH 10
#define MAP_HEIGHT 10


// 0: vide
// 1: mur infranchissable
// 9: chemin du A*
static int map[MAP_HEIGHT][MAP_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0, 3, 0},
    {0, 0, 1, 0, 0, 0, 1, 1, 1, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

static int node_cost(int x, int y)
{
    if (map[y][x] == 1) return (-1);
    return (1);
}

void print_map()
{
    int i;
    int j;

    for (i = 0; i < MAP_HEIGHT; i++) {
        for (j = 0; j < MAP_WIDTH; j++) {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    print_map();

    graph_t *graph = create_graph(MAP_WIDTH, MAP_HEIGHT);

    init_vertices(graph);

    int res_astar = astar_search(graph, node_cost,
        graph->vertices[8][1], graph->vertices[1][8]
    );
    printf("A* return result: %d\n", res_astar);

    if (res_astar) {
        vertice_t *path = graph->vertices[1][8];

        while (path) {
            map[path->y][path->x] = 9;
            path = path->predecessor;
        }
    }

    print_map();

    free_graph(graph);
    return (EXIT_SUCCESS);
}

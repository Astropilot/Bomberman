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

static vertice_t *map_nodes[MAP_HEIGHT][MAP_WIDTH];

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

void init_vertices()
{
    int i;
    int j;

    for (i = 0; i < MAP_HEIGHT; i++) {
        for (j = 0; j < MAP_WIDTH; j++) {
            vertice_t *vert;

            vert = new_vertice(j, i, (map[i][j] == 1 ? 0 : 1));
            map_nodes[i][j] = vert;
        }
    }
}

int main(void)
{
    int i;
    int j;

    print_map();

    init_vertices();

    graph_t *graph = create_graph(MAP_WIDTH, MAP_HEIGHT);

    for (i = 0; i < MAP_HEIGHT; i++) {
        for (j = 0; j < MAP_WIDTH; j++) {
            // Bloc du haut
            if (i - 1 >= 0)
                add_edge(graph, map_nodes[i][j], map_nodes[i-1][j]);
            // Bloc du bas
            if (i + 1 < MAP_HEIGHT)
                add_edge(graph, map_nodes[i][j], map_nodes[i+1][j]);
            // Bloc de gauche
            if (j - 1 >= 0)
                add_edge(graph, map_nodes[i][j], map_nodes[i][j-1]);
            // Bloc du bas
            if (j + 1 < MAP_WIDTH)
                add_edge(graph, map_nodes[i][j], map_nodes[i][j+1]);
        }
    }


    int res_astar = astar_search(graph, map_nodes[8][1], map_nodes[1][8]);
    printf("A* return result: %d\n", res_astar);

    if (res_astar) {
        vertice_t *path = map_nodes[1][8];

        while (path) {
            map[path->y][path->x] = 9;
            path = path->predecessor;
        }
    }

    print_map();

    for (i = 0; i < MAP_HEIGHT; i++) {
        for (j = 0; j < MAP_WIDTH; j++) {
            free(map_nodes[i][j]);
            map_nodes[i][j] = NULL;
        }
    }
    free_graph(graph);
    
    return (EXIT_SUCCESS);
}

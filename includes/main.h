/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file for the main program with some constants.
*/

#ifndef MAIN_H_
#define MAIN_H_

/***************************  UI CONSTS ***************************/

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

/***************************  GAME CONSTS *************************/

// MAX_PLAYERS and MIN_PLAYERS need to be lower or equal to 4.
#define MAX_PLAYERS 4
#define MIN_PLAYERS 2

#define MAP_START_PIX_X 368
#define MAP_START_PIX_Y 159

#define MAP_WIDTH 17
#define MAP_HEIGHT 15
#define MAP_BLOCK_SIZE 32

#define CHANCE_BREAKABLE_WALL 5

#define IS_DEBUG 0

typedef struct lobby_args_e {
    char *username;
    char *server_ip;
    int port;
} lobby_args_t ;

#endif

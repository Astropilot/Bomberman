/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file for the main program with some game constants.
*/

#ifndef MAIN_H_
#define MAIN_H_

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define IS_DEBUG 0

typedef struct lobby_args_e {
    char *username;
    char *server_ip;
    int port;
} lobby_args_t ;

#endif

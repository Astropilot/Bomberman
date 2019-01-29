/*
** ETNA PROJECT, 16/01/2019 by group
** gLib
** File description:
**      Graphic library with SDL2
*/

#ifndef RESLIB_MESSAGE_H_
#define RESLIB_MESSAGE_H_

#include <stdlib.h>

typedef struct TMessage {

    void *message;
    size_t len;
    int checksum;
    char[3] ender;

} TMessage ;

static char ENDER_MARK[3] = {0xFE, 0xFF, 0xFE};

#endif

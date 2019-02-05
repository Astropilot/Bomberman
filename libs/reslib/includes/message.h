/*
** ETNA PROJECT, 05/02/2019 by martin_h, hamide_a, despla_g, weber_w
** resLib
** File description:
**      Wrapper around the socket API.
*/

#ifndef RESLIB_MESSAGE_H_
#define RESLIB_MESSAGE_H_

#include <stdlib.h>

typedef struct TMessage {

    size_t len;
    char *message;
    //int checksum;

} TMessage ;



#endif

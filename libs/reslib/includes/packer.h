/*
** ETNA PROJECT, 05/02/2019 by martin_h, hamide_a, despla_g, weber_w
** resLib
** File description:
**      Wrapper around the socket API.
*/

#ifndef RESLIB_PACKER_H_
#define RESLIB_PACKER_H_

#include <stdlib.h>

char *pack_int(char *buffer, int i);
char *unpack_int(char *buffer, int *i);

#endif

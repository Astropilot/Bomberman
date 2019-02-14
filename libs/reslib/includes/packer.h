/*
** ETNA PROJECT, 05/02/2019 by martin_h, hamide_a, despla_g, weber_w
** resLib
** File description:
**      Wrapper around the socket API.
*/

#ifndef RESLIB_PACKER_H_
#define RESLIB_PACKER_H_

#include <stdlib.h>
#include <string.h>

char *pack_int(char *buffer, int i);
char *unpack_int(char *buffer, int *i);

char *pack_uint(char *buffer, unsigned int ui);
char *unpack_uint(char *buffer, unsigned int *ui);

char *pack_char(char *buffer, char chr);
char *unpack_char(char *buffer, char *chr);

char *pack_string(char *buffer, const char *str);
char *unpack_string(char *buffer, char *str);

#endif

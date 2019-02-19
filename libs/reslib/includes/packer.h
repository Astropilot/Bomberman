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

unsigned char *pack_int(unsigned char *buffer, int i);
unsigned char *unpack_int(unsigned char *buffer, int *i);

unsigned char *pack_uint(unsigned char *buffer, unsigned int ui);
unsigned char *unpack_uint(unsigned char *buffer, unsigned int *ui);

unsigned char *pack_char(unsigned char *buffer, char chr);
unsigned char *unpack_char(unsigned char *buffer, char *chr);

unsigned char *pack_string(unsigned char *buffer, const char *str);
unsigned char *unpack_string(unsigned char *buffer, char *str);

#endif

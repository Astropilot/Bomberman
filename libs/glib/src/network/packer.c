/*******************************************************************************
* PROJECT: gLib
*
* AUTHORS: Yohann Martin, Aziz Hamide, Gauthier Desplanque, William Weber
*
* DATE CREATED: 01/16/2019
*
* Copyright (c) 2019 Yohann MARTIN (@Astropilot). All rights reserved.
*
* Licensed under the MIT License. See LICENSE file in the project root for full
* license information.
*******************************************************************************/

#include <string.h>

#include "network/packer.h"

unsigned char *pack_int(unsigned char *buffer, int i)
{
    if (!buffer) return (NULL);

    *buffer++ = i >> 8;
    *buffer++ = i;
    return (buffer);
}

unsigned char *unpack_int(unsigned char *buffer, int *i)
{
    if (!buffer || !i) return (NULL);

    unsigned int ui = ((unsigned int)buffer[0] << 8) | buffer[1];
    int tmp_i;

    if (ui <= 0x7fffu)
        tmp_i = ui;
    else
        tmp_i = -1 - (unsigned int)(0xffffu - ui);
    *i = tmp_i;

    return (buffer + 2);
}

unsigned char *pack_uint(unsigned char *buffer, unsigned int ui)
{
    return pack_int(buffer, ui);
}

unsigned char *unpack_uint(unsigned char *buffer, unsigned int *ui)
{
    if (!buffer || !ui) return (NULL);

    *ui = ((unsigned int)buffer[0] << 8) | buffer[1];
    return (buffer + 2);
}

unsigned char *pack_char(unsigned char *buffer, char chr)
{
    if (!buffer) return (NULL);

    *buffer++ = chr;
    return (buffer);
}

unsigned char *unpack_char(unsigned char *buffer, char *chr)
{
    if (!buffer || !chr) return (NULL);

    *chr = *buffer;
    return (++buffer);
}

unsigned char *pack_string(unsigned char *buffer, const char *str)
{
    if (!buffer || !str) return (NULL);

    unsigned int len = (unsigned int)strlen(str);

    buffer = pack_uint(buffer, len);
    memcpy(buffer, str, len);
    return (buffer + len);
}

unsigned char *unpack_string(unsigned char *buffer, char *str)
{
    if (!buffer || !str) return (NULL);

    unsigned int len;

    buffer = unpack_uint(buffer, &len);
    memcpy(str, buffer, len);
    str[len] = '\0';
    return (buffer + len);
}

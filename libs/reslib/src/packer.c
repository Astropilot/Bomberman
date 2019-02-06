#include "packer.h"

char *pack_int(char *buffer, int i)
{
    *buffer++ = i>>8;
    *buffer++ = i;
    return (buffer);
}

char *unpack_int(char *buffer, int *i)
{
    unsigned int i2 = ((unsigned int)buffer[0]<<8) | buffer[1];
    int i3;

    // change unsigned numbers to signed
    if (i2 <= 0x7fffu) { i3 = i2; }
    else { i3 = -1 - (unsigned int)(0xffffu - i2); }
    *i = i3;

    return (buffer + 2);
}

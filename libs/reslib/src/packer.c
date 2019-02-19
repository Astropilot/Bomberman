#include "packer.h"

unsigned char *pack_int(unsigned char *buffer, int i)
{
    *buffer++ = i>>8;
    *buffer++ = i;
    return (buffer);
}

unsigned char *unpack_int(unsigned char *buffer, int *i)
{
    unsigned int i2 = ((unsigned int)buffer[0]<<8) | buffer[1];
    int i3;

    if (i2 <= 0x7fffu) { i3 = i2; }
    else { i3 = -1 - (unsigned int)(0xffffu - i2); }
    *i = i3;

    return (buffer + 2);
}

unsigned char *pack_uint(unsigned char *buffer, unsigned int ui)
{
    return pack_int(buffer, ui);
}

unsigned char *unpack_uint(unsigned char *buffer, unsigned int *ui)
{
    *ui = ((unsigned int)buffer[0]<<8) | buffer[1];
    return (buffer + 2);
}

unsigned char *pack_char(unsigned char *buffer, char chr)
{
    *buffer++ = chr;
    return (buffer);
}

unsigned char *unpack_char(unsigned char *buffer, char *chr)
{
    *chr = *buffer;
    return (++buffer);
}

unsigned char *pack_string(unsigned char *buffer, const char *str)
{
    int len = strlen(str);
    buffer = pack_int(buffer, len);
    memcpy(buffer, str, len);
    return (buffer + len);
}

unsigned char *unpack_string(unsigned char *buffer, char *str)
{
    int len;
    buffer = unpack_int(buffer, &len);
    memcpy(str, buffer, len);
    str[len] = '\0';
    return (buffer + len);
}

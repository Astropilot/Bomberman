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

    if (i2 <= 0x7fffu) { i3 = i2; }
    else { i3 = -1 - (unsigned int)(0xffffu - i2); }
    *i = i3;

    return (buffer + 2);
}

char *pack_uint(char *buffer, unsigned int ui)
{
    return pack_int(buffer, ui);
}

char *unpack_uint(char *buffer, unsigned int *ui)
{
    *ui = ((unsigned int)buffer[0]<<8) | buffer[1];
    return (buffer + 2);
}

char *pack_char(char *buffer, char chr)
{
    *buffer++ = chr;
    return (buffer);
}

char *unpack_char(char *buffer, char *chr)
{
    *chr = *buffer;
    return (++buffer);
}

char *pack_string(char *buffer, const char *str)
{
    int len = strlen(str);
    buffer = pack_int(buffer, len);
    memcpy(buffer, str, len);
    return (buffer + len);
}

char *unpack_string(char *buffer, char *str)
{
    int len;
    buffer = unpack_int(buffer, &len);
    memcpy(str, buffer, len);
    str[len] = '\0';
    return (buffer + len);
}

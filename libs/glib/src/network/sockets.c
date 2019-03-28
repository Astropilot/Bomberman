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

#include "network/sockets.h"

int InitNetworking(void)
{
    #ifdef _WIN32
        WSADATA wsa;
        return WSAStartup(MAKEWORD(2, 2), &wsa);
    #else
        return (0);
    #endif
}

int ResetNetworking(void)
{
    #ifdef _WIN32
        return WSACleanup();
    #else
        return (0);
    #endif
}

int SocketNonBlocking(SOCKET socket, unsigned int blocking)
{
    if (socket < 0) return (0);

    #ifdef _WIN32
        unsigned long mode = blocking ? 0 : 1;

        return (ioctlsocket(socket, FIONBIO, &mode) == 0) ? (1) : (0);
    #else
        int flags = fcntl(socket, F_GETFL, 0);

        if (flags == -1) return (0);
        flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
        return (fcntl(socket, F_SETFL, flags) == 0) ? (1) : (0);
    #endif
}

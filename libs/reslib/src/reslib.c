#include "sockets.h"
#include "reslib.h"

void init_network(void)
{
    #ifdef WIN32
        WSADATA wsa;
        int err = WSAStartup(MAKEWORD(2, 2), &wsa);

        if(err < 0) {
            puts("WSAStartup failed !");
            exit(EXIT_FAILURE);
        }
    #endif
}

void end_network(void)
{
    #ifdef WIN32
        WSACleanup();
    #endif
}

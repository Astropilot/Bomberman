/*
** ETNA PROJECT, 05/02/2019 by martin_h, hamide_a, despla_g, weber_w
** resLib
** File description:
**      Wrapper around the socket API.
*/

#ifndef RESLIB_H_
#define RESLIB_H_

#include <stdlib.h>

#include "message.h"
#include "client.h"
#include "server.h"

void init_network(void);
void end_network(void);

#endif

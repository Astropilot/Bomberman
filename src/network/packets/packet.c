/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the packet class.
*/

#include <string.h>

#include "network/packets/packet.h"
#include "network/network.h"

int extract_packet_id(unsigned char *raw_packet)
{
    int id_packet = -1;
    unpack_int(raw_packet, &id_packet);
    return (id_packet);
}

TMessage packet_to_message(TPacket *packet, unsigned int auto_free)
{
    int packet_size = packet->Serialize(packet);
    TMessage message = {packet_size, NULL};

    message.message = malloc(sizeof(unsigned char) * packet_size);
    memcpy(message.message, packet->raw_packet, packet_size);
    if (auto_free)
        packet->Free(packet);
    return (message);
}

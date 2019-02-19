/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the packet class.
*/

#include "network/packets/packet.h"
#include "reslib.h"

int extract_packet_id(unsigned char *raw_packet)
{
    int id_packet = -1;
    unpack_int(raw_packet, &id_packet);
    return (id_packet);
}

TMessage packet_to_message(TPacket *packet)
{
    int packet_size = packet->Serialize(packet);
    TMessage message = {packet_size, packet->raw_packet};

    return (message);
}

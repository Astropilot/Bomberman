/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the ack packet "lobby state".
*/

#ifndef PACKET_ACK_LOBBYSTATE_H_
#define PACKET_ACK_LOBBYSTATE_H_

typedef struct TAckLobbyStatePacket {

    int(*Serialize)(struct TAckLobbyStatePacket*);

    void(*Unserialize)(struct TAckLobbyStatePacket*);

    void(*Free)(struct TAckLobbyStatePacket*);

    unsigned char *raw_packet;
    int packet_id;
    unsigned int nb_players;

} TAckLobbyStatePacket ;

TAckLobbyStatePacket *New_TAckLobbyStatePacket(unsigned char *raw);
int TAckLobbyStatePacket_Serialize(TAckLobbyStatePacket *this);
void TAckLobbyStatePacket_Unserialize(TAckLobbyStatePacket *this);
void TAckLobbyStatePacket_New_Free(TAckLobbyStatePacket *this);

#endif

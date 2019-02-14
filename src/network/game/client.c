/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the game client component.
*/

#include <string.h>

#include "network/game/client.h"
#include "network/packets/packet.h"
#include "network/packets/packet_disconnect.h"
#include "network/packets/packet_ack_connect.h"
#include "network/packets/packet_ack_lobbystate.h"

static void On_Message(TClient *client, TMessage message);
static void On_Disconnect(TClient *client);

static TGameClient *game_client;

TGameClient* New_TGameClient()
{
    TGameClient *this = malloc(sizeof(TGameClient));

    if(!this) return NULL;

    this->client = New_TClient();
    this->client->On_Message = On_Message;
    this->client->On_Disconnect = On_Disconnect;
    game_client = this;
    this->username = NULL;
    this->Join_Game = TGameClient_Join_Game;
    this->Leave_Game = TGameClient_Leave_Game;
    this->Free = TGameClient_New_Free;
    return this;
}

int TGameClient_Join_Game(TGameClient *this, const char *username, const char *ip, int port)
{
    this->username = strdup(username);
    int res = this->client->Connect(this->client, ip, port);
    if (res == 0) {
        this->client->Start_Recv(this->client, NULL);
    }
}

void TGameClient_Leave_Game(TGameClient *this)
{
    this->client->Disconnect(this->client);
}

void On_Message(TClient *client, TMessage message)
{
    if (!server || !client) {
        printf("\nOn_Message Error\n");
        return;
    }
    if (message.len) {
        int packet_id = extract_packet_id(message.message);
        printf("Packed ID: %d\n", packet_id);
        if (packet_id == REQ_DISCONNECT) {
            TReqDisconnectPacket p_d = TReqDisconnectPacket(message.message);
            p_d->Unserialize(p_d);

            if (p_d->player != 0) {
                TAckLobbyStatePacket p = New_TAckLobbyStatePacket(NULL);

                p->nb_players = (int)server->CountClients(server) - 1;
                int packet_size = p->Serialize(p);
                TMessage message = {packet_size, p->raw_packet};
                this->server->Send_Broadcast(this->server, message);
                client->Disconnect(client);
            } else {
                TAckDisconnectPacket p = New_TAckDisconnectPacket(NULL);

                p->reason = MASTER_LEAVE;
                int packet_size = p->Serialize(p);
                TMessage message = {packet_size, p->raw_packet};
                this->server->Send_Broadcast(this->server, message);
            }
        }
        free(message.message);
    } else
        printf("\n[Server][On_Message] Client Disconnect\n");
    if (message.len == -1)
        printf("\n[Server][On_Message] Recv error !\n");
}

void On_Disconnect(TClient *client)
{
    if (client)
        printf("\n[Client][On_Disconnect] Server leave !\n");
    else
        printf("\n[Client][On_Disconnect] Error on disconnect\n");
}

void TGameClient_New_Free(TGameClient *this)
{
    if (this) {
        this->Leave_Game(this);
        this->client->Free(this->client);
    }
    free(this);
}

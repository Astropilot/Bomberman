/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the game server component.
*/

#include "network/game/server.h"
#include "network/packets/packet.h"
#include "network/packets/packet_disconnect.h"
#include "network/packets/packet_ack_connect.h"
#include "network/packets/packet_ack_lobbystate.h"

static void On_Client_Connect(TServer *server, TClient *client);
static void On_Message(TServer *server, TClient *client, TMessage message);
static void On_Disconnect(TServer *server, TClient *client);

static TGameServer *game_server;

TGameServer* New_TGameServer(int port, int max_clients)
{
    TGameServer *this = malloc(sizeof(TGameServer));

    if(!this) return NULL;

    this->server = New_TServer(port, 15);
    this->server->On_Connect = On_Client_Connect;
    this->server->On_Message = On_Message;
    this->server->On_Disconnect = On_Disconnect;
    game_server = this;
    this->max_clients = max_clients;
    this->Start = TGameServer_Start;
    this->Stop = TGameServer_Stop;
    this->Free = TGameServer_New_Free;
    return this;
}

void TGameServer_Start(TGameServer *this)
{
    this->server->Start_Listenning(this->server);
}

void TGameServer_Stop(TGameServer *this)
{
    TAckDisconnectPacket p = New_TAckDisconnectPacket(NULL);

    p->reason = MASTER_LEAVE;
    int packet_size = p->Serialize(p);
    TMessage message = {packet_size, p->raw_packet};
    this->server->Send_Broadcast(this->server, message);
    this->server->Stop_Listenning(this->server);
}

static void On_Client_Connect(TServer *server, TClient *client)
{
    if (client && server) {
        printf("\nNew client !\n");

        int nb_clients = (int)server->CountClients(server);

        if (game_server->max_clients <= nb_clients) {
            TAckConnectPacket p_a = TAckConnectPacket(NULL);
            TAckLobbyStatePacket p = New_TAckLobbyStatePacket(NULL);

            p_a->status = OK;
            p_a->player = nb_clients - 1;
            int packet_size = p_a->Serialize(p_a);
            TMessage message = {packet_size, p_a->raw_packet};
            client->Send(client, message);

            p->nb_players = nb_clients;
            packet_size = p->Serialize(p);
            message = {packet_size, p->raw_packet};
            server->Send_Broadcast(server, message);
        } else {
            TAckConnectPacket p_a = TAckConnectPacket(NULL);
            p_a->status = GAME_FULL;
            p_a->player = 0;
            int packet_size = p_a->Serialize(p_a);
            TMessage message = {packet_size, p_a->raw_packet};
            client->Send(client, message);
            client->Disconnect();
        }
    }
    else
        printf("\nError on connect\n");
}

void On_Message(TServer *server, TClient *client, TMessage message)
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

void On_Disconnect(TServer *server, TClient *client)
{
    if (client && server)
        printf("\n[Server][On_Disconnect] Client leave !\n");
    else
        printf("\n[Server][On_Disconnect] Error on disconnect\n");
}

void TGameServer_New_Free(TGameServer *this)
{
    if (this) {
        this->Stop(this);
        this->server->Free(this->server);
    }
    free(this);
}

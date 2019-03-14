/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the game server component.
*/

#include <stdio.h>
#include "network/game/server.h"

static void On_Message(TServer *server, TClient *client, TMessage message);

static TGameServer *game_server;

TGameServer* New_TGameServer()
{
    TGameServer *this = malloc(sizeof(TGameServer));

    if(!this) return NULL;

    game_server = this;
    this->server = NULL;
    this->max_clients = 0;
    this->nb_players = 0;
    this->ready_players = 0;
    this->map = NULL;
    this->Start = TGameServer_Start;
    this->Stop = TGameServer_Stop;
    this->Free = TGameServer_New_Free;
    return this;
}

void TGameServer_Start(TGameServer *this, int port, int max_clients)
{
    //int i;

    this->server = New_TServer(port, 15);
    this->server->On_Message = On_Message;
    this->max_clients = max_clients;
    /*this->players = malloc(sizeof(player_t) * max_clients);
    for (i = 0; i < max_clients; i++) {
        this->players[i].connected = 0;
    }*/
    this->map = New_TMap((size_t)max_clients);
    this->nb_players = 0;
    this->ready_players = 0;
    this->server->Start_Listenning(this->server);
}

void TGameServer_Stop(TGameServer *this)
{
    if (!this->server)
        return;
    TAckDisconnectPacket *p = New_TAckDisconnectPacket(NULL);

    p->reason = MASTER_LEAVE;
    this->server->Send_Broadcast(this->server, packet_to_message((TPacket*)p));
    this->server->Free(this->server);
    this->server = NULL;
    //free(this->players);
    this->map->Free(this->map);
    this->map = NULL;
    p->Free(p);
}

void On_Message(TServer *server, TClient *client, TMessage message)
{
    int packet_id = extract_packet_id(message.message);
    switch (packet_id) {
        case REQ_DISCONNECT:;
            TReqDisconnectPacket *p_d = New_TReqDisconnectPacket(message.message);
            p_d->Unserialize(p_d);

            if (p_d->player >= server->CountClients(server)) {
                p_d->Free(p_d);
                break;
            }
            reset_player(&(game_server->map->players[p_d->player]));
            if (p_d->player != 0) {
                TAckLobbyStatePacket *p = New_TAckLobbyStatePacket(NULL);

                game_server->nb_players--;
                p->nb_players = (int)game_server->nb_players;
                server->Send_Broadcast(server, packet_to_message((TPacket*)p));
                p->Free(p);
            }
            p_d->Free(p_d);
            break;
        case REQ_CONNECT:;
            TReqConnectPacket *p_rc = New_TReqConnectPacket(message.message);
            p_rc->Unserialize(p_rc);

            int nb_clients = (int)server->CountClients(server);
            if (nb_clients <= game_server->max_clients) {
                TAckConnectPacket *p_a = New_TAckConnectPacket(NULL);
                TAckLobbyStatePacket *p = New_TAckLobbyStatePacket(NULL);

                p_a->status = OK;
                p_a->player = next_id(game_server->map->players);
                init_player(&(game_server->map->players[p_a->player]), p_a->player, p_rc->player_name);
                client->Send(client, packet_to_message((TPacket*)p_a));
                p_a->Free(p_a);

                game_server->nb_players++;
                p->nb_players = game_server->nb_players;
                server->Send_Broadcast(server, packet_to_message((TPacket*)p));
                p->Free(p);
            } else {
                TAckConnectPacket *p_a = New_TAckConnectPacket(NULL);
                p_a->status = GAME_FULL;
                p_a->player = MAX_PLAYERS + 1;
                client->Send(client, packet_to_message((TPacket*)p_a));
                p_a->Free(p_a);
            }

            p_rc->Free(p_rc);
            break;
        case REQ_START_GAME:;
            TReqStartGamePacket *p_rs = New_TReqStartGamePacket(message.message);
            p_rs->Unserialize(p_rs);

            if (p_rs->player == 0) {
                TAckStartGamePacket *p = New_TAckStartGamePacket(NULL);

                game_server->map->Generate(game_server->map);
                server->Send_Broadcast(server, packet_to_message((TPacket*)p));
                p->Free(p);
            }

            p_rs->Free(p_rs);
            break;
        case REQ_READY:;
            TReqReadyPacket *p_rr = New_TReqReadyPacket(message.message);
            p_rr->Unserialize(p_rr);

            game_server->ready_players++;

            if (game_server->ready_players == game_server->nb_players) {
                TAckGameStatePacket *p = New_TAckGameStatePacket(NULL);

                p->nb_players = (unsigned int)game_server->nb_players;
                p->players = game_server->map->players;
                p->block_map = game_server->map->block_map;
                p->first_init = 1;
                server->Send_Broadcast(server, packet_to_message((TPacket*)p));
                p->Free(p);
            }

            p_rr->Free(p_rr);
            break;
        case REQ_MOVE:;
            TReqMovePlayerPacket *p_rm = New_TReqMovePlayerPacket(message.message);
            p_rm->Unserialize(p_rm);

            game_server->map->Move_Player(game_server->map, p_rm->player, p_rm->dir);

            TAckGameStatePacket *p = New_TAckGameStatePacket(NULL);

            p->nb_players = (unsigned int)game_server->nb_players;
            p->players = game_server->map->players;
            p->first_init = 0;
            p->block_map = NULL;
            server->Send_Broadcast(server, packet_to_message((TPacket*)p));
            p->Free(p);

            p_rm->Free(p_rm);
            break;
        case REQ_PLACE_BOMB:;
            TReqPlaceBombPacket *p_rb = New_TReqPlaceBombPacket(message.message);
            p_rb->Unserialize(p_rb);

            player_t player = game_server->map->players[p_rb->player];

            TAckPlaceBombPacket *p_ab = New_TAckPlaceBombPacket(NULL);

            p_ab->x = player.pos.x;
            p_ab->y = player.pos.y;
            server->Send_Broadcast(server, packet_to_message((TPacket*)p_ab));
            p_ab->Free(p_ab);

            p_rb->Free(p_rb);
            break;
        default:
            free(message.message);
    }
}

void TGameServer_New_Free(TGameServer *this)
{
    if (this) {
        if (this->map)
            this->map->Free(this->map);
    }
    free(this);
}

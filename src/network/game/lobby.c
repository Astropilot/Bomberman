/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Header file of the lobby client component.
*/

#include <string.h>

#include "network/game/lobby.h"
#include "network/packets/packet.h"
#include "main.h"

TLobbyClient* New_TLobbyClient()
{
    TLobbyClient *this = malloc(sizeof(TLobbyClient));

    if(!this) return NULL;

    this->client = NULL;
    this->gameserver = NULL;
    this->lobby_frame = NULL;
    this->username = NULL;
    this->is_owner = 0;
    this->player = -1;
    this->nb_players = 0;
    this->Register_Frame = TLobbyClient_Register_Frame;
    this->Start_Server = TLobbyClient_Start_Server;
    this->Join_Lobby = TLobbyClient_Join_Lobby;
    this->Start_Game = TLobbyClient_Start_Game;
    this->Handle_Messages = TLobbyClient_Handle_Messages;
    this->Leave_Lobby = TLobbyClient_Leave_Lobby;
    this->Free = TLobbyClient_New_Free;
    return this;
}

TFrame *TLobbyClient_Register_Frame(TLobbyClient *this, TFrame *frame)
{
    this->lobby_frame = frame;
    return (frame);
}

void TLobbyClient_Start_Server(TLobbyClient *this, int port, int max_clients)
{
    this->is_owner = 1;
    this->gameserver = New_TGameServer();
    this->gameserver->Start(this->gameserver, port, max_clients);
}

void TLobbyClient_Join_Lobby(TLobbyClient *this, const char *username, const char *ip, int port)
{
    this->client = New_TClient();
    this->username = strdup(username);
    int res = this->client->Connect(this->client, ip, port);
    if (res != 0) {
        this->Leave_Lobby(this);
    } else {
        TReqConnectPacket *p_rc = New_TReqConnectPacket(NULL);

        p_rc->player_name = strdup(this->username);
        this->client->Send(this->client, packet_to_message((TPacket*)p_rc));
        p_rc->Free(p_rc);
    }
}

void TLobbyClient_Start_Game(TLobbyClient *this)
{
    TReqStartGamePacket *p_rs = New_TReqStartGamePacket(NULL);

    p_rs->player = this->player;
    this->client->Send(this->client, packet_to_message((TPacket*)p_rs));
    p_rs->Free(p_rs);
}

void TLobbyClient_Handle_Messages(TLobbyClient *this)
{
    if (!this->client)
        return;

    TMessage message;
    int packet_id;
    int res_read = this->client->Recv(this->client, &message);
    if (res_read == EWOULDBLOCK || res_read == EAGAIN || message.len <= 0) return;

    packet_id = extract_packet_id(message.message);
    switch (packet_id) {
        case ACK_CONNECT:;
            TAckConnectPacket *p_ac = New_TAckConnectPacket(message.message);
            p_ac->Unserialize(p_ac);

            if (p_ac->status != OK)
                this->Leave_Lobby(this);
            else
                this->player = (int)p_ac->player;
            p_ac->Free(p_ac);
            break;
        case ACK_DISCONNECT:;
            free(message.message);
            this->Leave_Lobby(this);
            break;
        case ACK_LOBBY_STATE:;
            TText *txt_label = (TText*)this->lobby_frame->Remove_Drawable(this->lobby_frame, "LABEL_STATUS");
            TAckLobbyStatePacket *p_as = New_TAckLobbyStatePacket(message.message);
            txt_label->Free(txt_label);

            p_as->Unserialize(p_as);
            this->nb_players = p_as->nb_players;
            char *status = malloc(sizeof(char) * 255);
            sprintf(status, "Nombre de joueurs presents: %d/4", this->nb_players);

            SDL_Rect pos_label = {0, 0, 0, 0};
            SDL_Color color = {255, 255, 255, 255};
            txt_label = New_TText(this->lobby_frame, status, TTF_OpenFont("fonts/fixedsys.ttf", 24), color, pos_label);
            txt_label->pos.x = (WIN_WIDTH / 2) - (txt_label->pos.w / 2);
            txt_label->pos.y = (WIN_HEIGHT / 2) - (txt_label->pos.h / 2);
            this->lobby_frame->Add_Drawable(this->lobby_frame, (TDrawable*)txt_label, "LABEL_STATUS", 1);

            free(status);
            p_as->Free(p_as);
            break;
        case ACK_START_GAME:;
            free(message.message);
            free(this->username);
            this->username = NULL;
            this->lobby_frame->window->Show_Frame(
                this->lobby_frame->window,
                "FRAME_GAME",
                4, this->client, this->gameserver, this->player, this->nb_players
            );
            break;
        default:
            free(message.message);
    }
}

void TLobbyClient_Leave_Lobby(TLobbyClient *this)
{
    if (!(this->client))
        return;

    TReqDisconnectPacket *p_d = New_TReqDisconnectPacket(NULL);
    p_d->reason = (this->is_owner ? MASTER_LEAVE : USER_QUIT);
    p_d->player = (unsigned int)this->player;
    this->client->Send(this->client, packet_to_message((TPacket*)p_d));
    this->client->Disconnect(this->client);
    this->client->Free(this->client);
    this->client = NULL;
    free(this->username);
    this->username = NULL;
    this->is_owner = 0;
    this->player = -1;
    if (this->gameserver) {
        this->gameserver->Stop(this->gameserver);
        this->gameserver->Free(this->gameserver);
        this->gameserver = NULL;
    }
    this->lobby_frame->window->Show_Frame(this->lobby_frame->window, "FRAME_MAIN_MENU", 0);
}

void TLobbyClient_New_Free(TLobbyClient *this)
{
    free(this);
}

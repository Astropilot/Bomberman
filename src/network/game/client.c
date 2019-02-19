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

TGameClient* New_TGameClient()
{
    TGameClient *this = malloc(sizeof(TGameClient));

    if(!this) return NULL;

    this->client = NULL;
    this->gameserver = NULL;
    this->game_frame = NULL;
    this->is_owner = 0;
    this->player = -1;
    this->Register_Frame = TGameClient_Register_Frame;
    this->Ready = TGameClient_Ready;
    this->Move = TGameClient_Move;
    this->Place_Bomb = TGameClient_Place_Bomb;
    this->Handle_Messages = TGameClient_Handle_Messages;
    this->Leave_Game = TGameClient_Leave_Game;
    this->Free = TGameClient_New_Free;
    return this;
}

TFrame *TGameClient_Register_Frame(TGameClient *this, TFrame *frame)
{
    this->game_frame = frame;
    return (frame);
}

void TGameClient_Ready(TGameClient *this)
{
    TReqReadyPacket *p_rr = New_TReqReadyPacket(NULL);

    p_rr->player = this->player;
    this->client->Send(this->client, packet_to_message((TPacket*)p_rr));
    p_rr->Free(p_rr);
}

void TGameClient_Move(TGameClient *this, direction_t direction)
{
    TReqMovePlayerPacket *p_rm = New_TReqMovePlayerPacket(NULL);

    p_rm->dir = (unsigned int)direction;
    p_rm->player = this->player;
    this->client->Send(this->client, packet_to_message((TPacket*)p_rm));
    p_rm->Free(p_rm);
}

void TGameClient_Place_Bomb(TGameClient *this)
{
    TReqPlaceBombPacket *p_rb = New_TReqPlaceBombPacket(NULL);

    p_rb->player = this->player;
    this->client->Send(this->client, packet_to_message((TPacket*)p_rb));
    p_rb->Free(p_rb);
}

void TGameClient_Handle_Messages(TGameClient *this)
{
    if (!this->client)
        return;

    TMessage message;
    int packet_id;
    int res_read = this->client->Recv(this->client, &message);
    if (res_read == EWOULDBLOCK || res_read == EAGAIN || message.len <= 0) return;

    packet_id = extract_packet_id(message.message);
    switch (packet_id) {
        case ACK_DISCONNECT:;
            free(message.message);
            this->Leave_Game(this);
            break;
        case ACK_GAME_STATE:;
            TAckGameStatePacket *p_as = New_TAckGameStatePacket(message.message);
            p_as->Unserialize(p_as);

            unsigned int i;
            for (i = 0; i < p_as->nb_players; i++) {
                char *player_id = malloc(sizeof(char) * 10);
                player_t player = p_as->players[i];
                sprintf(player_id, "PLAYER_%d", (int)i);
                TAnimatedSprite *asp = (TAnimatedSprite*)this->game_frame->Get_Drawable(this->game_frame, player_id);
                asp->pos.x = player.x;
                asp->pos.y = player.y;
                free(player_id);
            }

            p_as->Free(p_as);
            break;
        case ACK_PLACE_BOMB:;
            TAckPlaceBombPacket *p_ab = New_TAckPlaceBombPacket(message.message);
            p_ab->Unserialize(p_ab);

            SDL_Rect size_bomb = {0, 0, 256, 256};
            SDL_Rect pos_bomb = {p_ab->x, p_ab->y, 32, 32};
            TAnimatedSprite *sp = New_TAnimatedSprite(
                this->game_frame, "images/bomberman_bomb_animated.png",
                size_bomb, pos_bomb, 128, 1
            );
            this->game_frame->Add_Drawable(this->game_frame, (TDrawable*)sp, "BOMB", 2);

            p_ab->Free(p_ab);
            break;
        default:
            free(message.message);
    }
}

void TGameClient_Leave_Game(TGameClient *this)
{
    TReqDisconnectPacket *p_d = New_TReqDisconnectPacket(NULL);
    p_d->reason = (this->is_owner ? MASTER_LEAVE : USER_QUIT);
    p_d->player = (unsigned int)this->player;
    this->client->Send(this->client, packet_to_message((TPacket*)p_d));
    this->client->Disconnect(this->client);
    this->client->Free(this->client);
    this->client = NULL;
    this->is_owner = 0;
    this->player = -1;
    if (this->gameserver) {
        this->gameserver->Stop(this->gameserver);
        this->gameserver->Free(this->gameserver);
        this->gameserver = NULL;
    }
    this->game_frame->window->Show_Frame(this->game_frame->window, "FRAME_MAIN_MENU", 0);
}

void TGameClient_New_Free(TGameClient *this)
{
    if (this) {
        this->Leave_Game(this);
    }
    free(this);
}

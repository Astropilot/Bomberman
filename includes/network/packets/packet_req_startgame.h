/*******************************************************************************
* PROJECT: Bomberman
*
* AUTHORS: Yohann Martin, Aziz Hamide, Gauthier Desplanque, William Weber
*
* DATE CREATED: 01/16/2019
*
* Copyright (c) 2019 Yohann MARTIN (@Astropilot). All rights reserved.
*
* Licensed under the MIT License. See LICENSE file in the project root for full
* license information.
*******************************************************************************/

/**
 * @file network/packets/packet_req_startgame.h
 * @brief Header file of the TReqStartGamePacket class.
 *
 * The TReqStartGamePacket class is a high-level packet.
 *
 */

#ifndef PACKET_REQ_STARTGAME_H_
#define PACKET_REQ_STARTGAME_H_

/**
 * @brief An class representing the client request start game packet.
 *
 * TReqStartGamePacket is a class representing the client request start game packet.
 */
typedef struct TReqStartGamePacket {

    int(*Serialize)(struct TReqStartGamePacket*);       /*!< Method to serialize the high-level packet. */

    void(*Unserialize)(struct TReqStartGamePacket*);    /*!< Method to de-serialize the high-level packet. */

    void(*Free)(struct TReqStartGamePacket*);           /*!< Free (ressources) method. */

    unsigned char *raw_packet;                          /*!< The low-leve buffer when packet is serialized. */
    int packet_id;                                      /*!< The packet ID. */
    unsigned int player;                                /*!< The ID of the player who want to start game. */

} TReqStartGamePacket ;

/**
 * @brief The constructor for create a TReqStartGamePacket object.
 *
 * @return A memory allocated object of the packet.
 */
TReqStartGamePacket *New_TReqStartGamePacket(unsigned char *raw);

/**
 * @brief Method to serialize the packet into a low-level buffer.
 *
 * @param this A pointer to the packet object.
 * @return Returns the low-level buffer length.
 *
 * You do not have to call this method directly. You must use the
 * Serialize method of the TReqStartGamePacket structure like this:
 * my_packet->Serialize(my_packet);
 */
int TReqStartGamePacket_Serialize(TReqStartGamePacket *this);

/**
 * @brief Method to de-serialize the low-level buffer into the packet.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Unserialize method of the TReqStartGamePacket structure like this:
 * my_packet->Unserialize(my_packet);
 */
void TReqStartGamePacket_Unserialize(TReqStartGamePacket *this);

/**
 * @brief Method to free the resource take by the object.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TReqStartGamePacket structure like this:
 * my_packet->Free(my_packet);
 */
void TReqStartGamePacket_New_Free(TReqStartGamePacket *this);

#endif

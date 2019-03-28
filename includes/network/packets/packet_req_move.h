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
 * @file packet_req_move.h
 * @brief Header file of the TReqMovePlayerPacket class.
 *
 * The TReqMovePlayerPacket class is a high-level packet.
 *
 */

#ifndef PACKET_REQ_MOVEPLAYER_H_
#define PACKET_REQ_MOVEPLAYER_H_

/**
 * @brief An class representing the client request move packet.
 *
 * TReqMovePlayerPacket is a class representing the client request move packet.
 */
typedef struct TReqMovePlayerPacket {

    int(*Serialize)(struct TReqMovePlayerPacket*);      /*!< Method to serialize the high-level packet. */

    void(*Unserialize)(struct TReqMovePlayerPacket*);   /*!< Method to de-serialize the high-level packet. */

    void(*Free)(struct TReqMovePlayerPacket*);          /*!< Free (ressources) method. */

    unsigned char *raw_packet;                          /*!< The low-leve buffer when packet is serialized. */
    int packet_id;                                      /*!< The packet ID. */
    unsigned int dir;                                   /*!< The direction wanted. */
    unsigned int player;                                /*!< The ID of the player who want to move. */

} TReqMovePlayerPacket ;

/**
 * @fn TReqMovePlayerPacket *New_TReqMovePlayerPacket(unsigned char *raw)
 * @brief The constructor for create a TReqMovePlayerPacket object.
 *
 * @return A memory allocated object of the packet.
 */
TReqMovePlayerPacket *New_TReqMovePlayerPacket(unsigned char *raw);

/**
 * @fn int TReqMovePlayerPacket_Serialize(TReqMovePlayerPacket *this)
 * @brief Method to serialize the packet into a low-level buffer.
 *
 * @param this A pointer to the packet object.
 * @return Returns the low-level buffer length.
 *
 * You do not have to call this method directly. You must use the
 * Serialize method of the TReqMovePlayerPacket structure like this:
 * my_packet->Serialize(my_packet);
 */
int TReqMovePlayerPacket_Serialize(TReqMovePlayerPacket *this);

/**
 * @fn void TReqMovePlayerPacket_Unserialize(TReqMovePlayerPacket *this)
 * @brief Method to de-serialize the low-level buffer into the packet.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Unserialize method of the TReqMovePlayerPacket structure like this:
 * my_packet->Unserialize(my_packet);
 */
void TReqMovePlayerPacket_Unserialize(TReqMovePlayerPacket *this);

/**
 * @fn void TReqMovePlayerPacket_New_Free(TReqMovePlayerPacket *this)
 * @brief Method to free the resource take by the object.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TReqMovePlayerPacket structure like this:
 * my_packet->Free(my_packet);
 */
void TReqMovePlayerPacket_New_Free(TReqMovePlayerPacket *this);

#endif

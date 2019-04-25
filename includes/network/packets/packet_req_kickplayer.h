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
 * @file network/packets/packet_req_kickplayer.h
 * @brief Header file of the TReqKickPlayerPacket class.
 *
 * The TReqKickPlayerPacket class is a high-level packet.
 *
 */

#ifndef PACKET_REQ_KICKPLAYER_H_
#define PACKET_REQ_KICKPLAYER_H_

/**
 * @brief An class representing the client request kick player packet.
 *
 * TReqKickPlayerPacket is a class representing the client request kick player packet.
 */
typedef struct TReqKickPlayerPacket {

    int(*Serialize)(struct TReqKickPlayerPacket*);       /*!< Method to serialize the high-level packet. */

    void(*Unserialize)(struct TReqKickPlayerPacket*);    /*!< Method to de-serialize the high-level packet. */

    void(*Free)(struct TReqKickPlayerPacket*);           /*!< Free (ressources) method. */

    unsigned char *raw_packet;                          /*!< The low-leve buffer when packet is serialized. */
    int packet_id;                                      /*!< The packet ID. */
    unsigned int player;                                /*!< The ID of the player who want to kick. */
    unsigned int kick_id;                               /*!< The ID of the player to kick. */

} TReqKickPlayerPacket ;

/**
 * @brief The constructor for create a TReqKickPlayerPacket object.
 *
 * @return A memory allocated object of the packet.
 */
TReqKickPlayerPacket *New_TReqKickPlayerPacket(unsigned char *raw);

/**
 * @brief Method to serialize the packet into a low-level buffer.
 *
 * @param this A pointer to the packet object.
 * @return Returns the low-level buffer length.
 *
 * You do not have to call this method directly. You must use the
 * Serialize method of the TReqKickPlayerPacket structure like this:
 * my_packet->Serialize(my_packet);
 */
int TReqKickPlayerPacket_Serialize(TReqKickPlayerPacket *this);

/**
 * @brief Method to de-serialize the low-level buffer into the packet.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Unserialize method of the TReqKickPlayerPacket structure like this:
 * my_packet->Unserialize(my_packet);
 */
void TReqKickPlayerPacket_Unserialize(TReqKickPlayerPacket *this);

/**
 * @brief Method to free the resource take by the object.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TReqKickPlayerPacket structure like this:
 * my_packet->Free(my_packet);
 */
void TReqKickPlayerPacket_New_Free(TReqKickPlayerPacket *this);

#endif

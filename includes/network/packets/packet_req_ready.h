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
 * @file network/packets/packet_req_ready.h
 * @brief Header file of the TReqReadyPacket class.
 *
 * The TReqReadyPacket class is a high-level packet.
 *
 */

#ifndef PACKET_REQ_READY_H_
#define PACKET_REQ_READY_H_

/**
 * @brief An class representing the client request ready packet.
 *
 * TReqReadyPacket is a class representing the client request ready packet.
 */
typedef struct TReqReadyPacket {

    int(*Serialize)(struct TReqReadyPacket*);       /*!< Method to serialize the high-level packet. */

    void(*Unserialize)(struct TReqReadyPacket*);    /*!< Method to de-serialize the high-level packet. */

    void(*Free)(struct TReqReadyPacket*);           /*!< Free (ressources) method. */

    unsigned char *raw_packet;                      /*!< The low-leve buffer when packet is serialized. */
    int packet_id;                                  /*!< The packet ID. */
    unsigned int player;                            /*!< The ID of the player who is ready. */

} TReqReadyPacket ;

/**
 * @fn TReqReadyPacket *New_TReqReadyPacket(unsigned char *raw)
 * @brief The constructor for create a TReqReadyPacket object.
 *
 * @return A memory allocated object of the packet.
 */
TReqReadyPacket *New_TReqReadyPacket(unsigned char *raw);

/**
 * @fn int TReqReadyPacket_Serialize(TReqReadyPacket *this)
 * @brief Method to serialize the packet into a low-level buffer.
 *
 * @param this A pointer to the packet object.
 * @return Returns the low-level buffer length.
 *
 * You do not have to call this method directly. You must use the
 * Serialize method of the TReqReadyPacket structure like this:
 * my_packet->Serialize(my_packet);
 */
int TReqReadyPacket_Serialize(TReqReadyPacket *this);

/**
 * @fn void TReqReadyPacket_Unserialize(TReqReadyPacket *this)
 * @brief Method to de-serialize the low-level buffer into the packet.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Unserialize method of the TReqReadyPacket structure like this:
 * my_packet->Unserialize(my_packet);
 */
void TReqReadyPacket_Unserialize(TReqReadyPacket *this);

/**
 * @fn void TReqReadyPacket_New_Free(TReqReadyPacket *this)
 * @brief Method to free the resource take by the object.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TReqReadyPacket structure like this:
 * my_packet->Free(my_packet);
 */
void TReqReadyPacket_New_Free(TReqReadyPacket *this);

#endif

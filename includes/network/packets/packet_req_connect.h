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
 * @file packet_req_connect.h
 * @brief Header file of the TReqConnectPacket class.
 *
 * The TReqConnectPacket class is a high-level packet.
 *
 */

#ifndef PACKET_REQ_CONNECT_H_
#define PACKET_REQ_CONNECT_H_

/**
 * @brief An class representing the client request connect packet.
 *
 * TReqConnectPacket is a class representing the client request connect packet.
 */
typedef struct TReqConnectPacket {

    int(*Serialize)(struct TReqConnectPacket*);     /*!< Method to serialize the high-level packet. */

    void(*Unserialize)(struct TReqConnectPacket*);  /*!< Method to de-serialize the high-level packet. */

    void(*Free)(struct TReqConnectPacket*);         /*!< Free (ressources) method. */

    unsigned char *raw_packet;                      /*!< The low-leve buffer when packet is serialized. */
    int packet_id;                                  /*!< The packet ID. */
    char *player_name;                              /*!< The username of the player. */

} TReqConnectPacket ;

/**
 * @fn TReqConnectPacket *New_TReqConnectPacket(unsigned char *raw)
 * @brief The constructor for create a TReqConnectPacket object.
 *
 * @return A memory allocated object of the packet.
 */
TReqConnectPacket *New_TReqConnectPacket(unsigned char *raw);

/**
 * @fn int TReqConnectPacket_Serialize(TReqConnectPacket *this)
 * @brief Method to serialize the packet into a low-level buffer.
 *
 * @param this A pointer to the packet object.
 * @return Returns the low-level buffer length.
 *
 * You do not have to call this method directly. You must use the
 * Serialize method of the TReqConnectPacket structure like this:
 * my_packet->Serialize(my_packet);
 */
int TReqConnectPacket_Serialize(TReqConnectPacket *this);

/**
 * @fn void TReqConnectPacket_Unserialize(TReqConnectPacket *this)
 * @brief Method to de-serialize the low-level buffer into the packet.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Unserialize method of the TReqConnectPacket structure like this:
 * my_packet->Unserialize(my_packet);
 */
void TReqConnectPacket_Unserialize(TReqConnectPacket *this);

/**
 * @fn void TReqConnectPacket_New_Free(TReqConnectPacket *this)
 * @brief Method to free the resource take by the object.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TReqConnectPacket structure like this:
 * my_packet->Free(my_packet);
 */
void TReqConnectPacket_New_Free(TReqConnectPacket *this);

#endif

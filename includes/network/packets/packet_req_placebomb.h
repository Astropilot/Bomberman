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
 * @file packet_req_placebomb.h
 * @brief Header file of the TReqPlaceBombPacket class.
 *
 * The TReqPlaceBombPacket class is a high-level packet.
 *
 */

#ifndef PACKET_REQ_PLACEBOMB_H_
#define PACKET_REQ_PLACEBOMB_H_

/**
 * @brief An class representing the client request place bomb packet.
 *
 * TReqPlaceBombPacket is a class representing the client request place bomb packet.
 */
typedef struct TReqPlaceBombPacket {

    int(*Serialize)(struct TReqPlaceBombPacket*);       /*!< Method to serialize the high-level packet. */

    void(*Unserialize)(struct TReqPlaceBombPacket*);    /*!< Method to de-serialize the high-level packet. */

    void(*Free)(struct TReqPlaceBombPacket*);           /*!< Free (ressources) method. */

    unsigned char *raw_packet;                          /*!< The low-leve buffer when packet is serialized. */
    int packet_id;                                      /*!< The packet ID. */
    unsigned int player;                                /*!< The ID of the player who want to drop a bomb. */

} TReqPlaceBombPacket ;

/**
 * @fn TReqPlaceBombPacket *New_TReqPlaceBombPacket(unsigned char *raw)
 * @brief The constructor for create a TReqPlaceBombPacket object.
 *
 * @return A memory allocated object of the packet.
 */
TReqPlaceBombPacket *New_TReqPlaceBombPacket(unsigned char *raw);

/**
 * @fn int TReqPlaceBombPacket_Serialize(TReqPlaceBombPacket *this)
 * @brief Method to serialize the packet into a low-level buffer.
 *
 * @param this A pointer to the packet object.
 * @return Returns the low-level buffer length.
 *
 * You do not have to call this method directly. You must use the
 * Serialize method of the TReqPlaceBombPacket structure like this:
 * my_packet->Serialize(my_packet);
 */
int TReqPlaceBombPacket_Serialize(TReqPlaceBombPacket *this);

/**
 * @fn void TReqPlaceBombPacket_Unserialize(TReqPlaceBombPacket *this)
 * @brief Method to de-serialize the low-level buffer into the packet.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Unserialize method of the TReqPlaceBombPacket structure like this:
 * my_packet->Unserialize(my_packet);
 */
void TReqPlaceBombPacket_Unserialize(TReqPlaceBombPacket *this);

/**
 * @fn void TReqPlaceBombPacket_New_Free(TReqPlaceBombPacket *this)
 * @brief Method to free the resource take by the object.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TReqPlaceBombPacket structure like this:
 * my_packet->Free(my_packet);
 */
void TReqPlaceBombPacket_New_Free(TReqPlaceBombPacket *this);

#endif

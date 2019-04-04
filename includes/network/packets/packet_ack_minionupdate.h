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
 * @file network/packets/packet_ack_move.h
 * @brief Header file of the TAckMinionUpdatePacket class.
 *
 * The TAckMinionUpdatePacket class is a high-level packet.
 *
 */

#ifndef PACKET_ACK_MINIONUPDATE_H_
#define PACKET_ACK_MINIONUPDATE_H_

#include "core/utils.h"

/**
 * @brief An class representing the server response move packet.
 *
 * TAckMinionUpdatePacket is a class representing the server response move packet.
 */
typedef struct TAckMinionUpdatePacket {

    int(*Serialize)(struct TAckMinionUpdatePacket*);        /*!< Method to serialize the high-level packet. */

    void(*Unserialize)(struct TAckMinionUpdatePacket*);     /*!< Method to de-serialize the high-level packet. */

    void(*Free)(struct TAckMinionUpdatePacket*);            /*!< Free (ressources) method. */

    unsigned char *raw_packet;                      /*!< The low-leve buffer when packet is serialized. */
    int packet_id;                                  /*!< The packet ID. */
    pos_t minion_pos;                               /*!< The minion position. */

} TAckMinionUpdatePacket ;

/**
 * @fn TAckMinionUpdatePacket *New_TAckMinionUpdatePacket(unsigned char *raw)
 * @brief The constructor for create a TAckMinionUpdatePacket object.
 *
 * @return A memory allocated object of the packet.
 */
TAckMinionUpdatePacket *New_TAckMinionUpdatePacket(unsigned char *raw);

/**
 * @fn int TAckMinionUpdatePacket_Serialize(TAckMinionUpdatePacket *this)
 * @brief Method to serialize the packet into a low-level buffer.
 *
 * @param this A pointer to the packet object.
 * @return Returns the low-level buffer length.
 *
 * You do not have to call this method directly. You must use the
 * Serialize method of the TAckMinionUpdatePacket structure like this:
 * my_packet->Serialize(my_packet);
 */
int TAckMinionUpdatePacket_Serialize(TAckMinionUpdatePacket *this);

/**
 * @fn void TAckMinionUpdatePacket_Unserialize(TAckMinionUpdatePacket *this)
 * @brief Method to de-serialize the low-level buffer into the packet.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Unserialize method of the TAckMinionUpdatePacket structure like this:
 * my_packet->Unserialize(my_packet);
 */
void TAckMinionUpdatePacket_Unserialize(TAckMinionUpdatePacket *this);

/**
 * @fn void TAckMinionUpdatePacket_New_Free(TAckMinionUpdatePacket *this)
 * @brief Method to free the resource take by the object.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TAckMinionUpdatePacket structure like this:
 * my_packet->Free(my_packet);
 */
void TAckMinionUpdatePacket_New_Free(TAckMinionUpdatePacket *this);

#endif

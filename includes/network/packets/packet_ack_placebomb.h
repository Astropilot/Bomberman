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
 * @file network/packets/packet_ack_placebomb.h
 * @brief Header file of the TAckPlaceBombPacket class.
 *
 * The TAckPlaceBombPacket class is a high-level packet.
 *
 */

#ifndef PACKET_ACK_PLACEBOMB_H_
#define PACKET_ACK_PLACEBOMB_H_

#include "core/bomb.h"

/**
 * @brief An class representing the server response place bomb packet.
 *
 * TAckPlaceBombPacket is a class representing the server response place bomb packet.
 */
typedef struct TAckPlaceBombPacket {

    int(*Serialize)(struct TAckPlaceBombPacket*);       /*!< Method to serialize the high-level packet. */

    void(*Unserialize)(struct TAckPlaceBombPacket*);    /*!< Method to de-serialize the high-level packet. */

    void(*Free)(struct TAckPlaceBombPacket*);           /*!< Free (ressources) method. */

    unsigned char *raw_packet;                          /*!< The low-leve buffer when packet is serialized. */
    int packet_id;                                      /*!< The packet ID. */
    bomb_status_t status;                               /*!< The status of the drop request. */
    bomb_reason_t reason;                               /*!< The possible reason if drop failed. */
    unsigned int bomb_id;                               /*!< The ID of the bomb dropped. */
    unsigned int x;                                     /*!< The x-axis position of the bomb. */
    unsigned int y;                                     /*!< The y-axis position of the bomb. */

} TAckPlaceBombPacket ;

/**
 * @fn TAckPlaceBombPacket *New_TAckPlaceBombPacket(unsigned char *raw)
 * @brief The constructor for create a TAckPlaceBombPacket object.
 *
 * @return A memory allocated object of the packet.
 */
TAckPlaceBombPacket *New_TAckPlaceBombPacket(unsigned char *raw);

/**
 * @fn int TAckPlaceBombPacket_Serialize(TAckPlaceBombPacket *this)
 * @brief Method to serialize the packet into a low-level buffer.
 *
 * @param this A pointer to the packet object.
 * @return Returns the low-level buffer length.
 *
 * You do not have to call this method directly. You must use the
 * Serialize method of the TAckPlaceBombPacket structure like this:
 * my_packet->Serialize(my_packet);
 */
int TAckPlaceBombPacket_Serialize(TAckPlaceBombPacket *this);

/**
 * @fn void TAckPlaceBombPacket_Unserialize(TAckPlaceBombPacket *this)
 * @brief Method to de-serialize the low-level buffer into the packet.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Unserialize method of the TAckPlaceBombPacket structure like this:
 * my_packet->Unserialize(my_packet);
 */
void TAckPlaceBombPacket_Unserialize(TAckPlaceBombPacket *this);

/**
 * @fn void TAckPlaceBombPacket_New_Free(TAckPlaceBombPacket *this)
 * @brief Method to free the resource take by the object.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TAckPlaceBombPacket structure like this:
 * my_packet->Free(my_packet);
 */
void TAckPlaceBombPacket_New_Free(TAckPlaceBombPacket *this);

#endif

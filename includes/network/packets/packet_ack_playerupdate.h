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
 * @file packet_ack_playerupdate.h
 * @brief Header file of the TAckPlayerUpdatePacket class.
 *
 * The TAckPlayerUpdatePacket class is a high-level packet.
 *
 */

#ifndef PACKET_ACK_PLAYERUPDATE_H_
#define PACKET_ACK_PLAYERUPDATE_H_

#include "core/player.h"

/**
 * @brief An class representing the server response player update packet.
 *
 * TAckPlayerUpdatePacket is a class representing the server response player update packet.
 */
typedef struct TAckPlayerUpdatePacket {

    int(*Serialize)(struct TAckPlayerUpdatePacket*);        /*!< Method to serialize the high-level packet. */

    void(*Unserialize)(struct TAckPlayerUpdatePacket*);     /*!< Method to de-serialize the high-level packet. */

    void(*Free)(struct TAckPlayerUpdatePacket*);            /*!< Free (ressources) method. */

    unsigned char *raw_packet;                              /*!< The low-leve buffer when packet is serialized. */
    int packet_id;                                          /*!< The packet ID. */
    player_t player;                                        /*!< The updated player. */

} TAckPlayerUpdatePacket ;

/**
 * @fn TAckPlayerUpdatePacket *New_TAckPlayerUpdatePacket(unsigned char *raw)
 * @brief The constructor for create a TAckPlayerUpdatePacket object.
 *
 * @return A memory allocated object of the packet.
 */
TAckPlayerUpdatePacket *New_TAckPlayerUpdatePacket(unsigned char *raw);

/**
 * @fn int TAckPlayerUpdatePacket_Serialize(TAckPlayerUpdatePacket *this)
 * @brief Method to serialize the packet into a low-level buffer.
 *
 * @param this A pointer to the packet object.
 * @return Returns the low-level buffer length.
 *
 * You do not have to call this method directly. You must use the
 * Serialize method of the TAckPlayerUpdatePacket structure like this:
 * my_packet->Serialize(my_packet);
 */
int TAckPlayerUpdatePacket_Serialize(TAckPlayerUpdatePacket *this);

/**
 * @fn void TAckPlayerUpdatePacket_Unserialize(TAckPlayerUpdatePacket *this)
 * @brief Method to de-serialize the low-level buffer into the packet.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Unserialize method of the TAckPlayerUpdatePacket structure like this:
 * my_packet->Unserialize(my_packet);
 */
void TAckPlayerUpdatePacket_Unserialize(TAckPlayerUpdatePacket *this);

/**
 * @fn void TAckPlayerUpdatePacket_New_Free(TAckPlayerUpdatePacket *this)
 * @brief Method to free the resource take by the object.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TAckPlayerUpdatePacket structure like this:
 * my_packet->Free(my_packet);
 */
void TAckPlayerUpdatePacket_New_Free(TAckPlayerUpdatePacket *this);

#endif

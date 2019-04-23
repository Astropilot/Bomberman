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
 * @brief Header file of the TAckMovePacket class.
 *
 * The TAckMovePacket class is a high-level packet.
 *
 */

#ifndef PACKET_ACK_MOVE_H_
#define PACKET_ACK_MOVE_H_

#include "core/player.h"

/**
 * @brief An class representing the server response move packet.
 *
 * TAckMovePacket is a class representing the server response move packet.
 */
typedef struct TAckMovePacket {

    int(*Serialize)(struct TAckMovePacket*);        /*!< Method to serialize the high-level packet. */

    void(*Unserialize)(struct TAckMovePacket*);     /*!< Method to de-serialize the high-level packet. */

    void(*Free)(struct TAckMovePacket*);            /*!< Free (ressources) method. */

    unsigned char *raw_packet;                      /*!< The low-leve buffer when packet is serialized. */
    int packet_id;                                  /*!< The packet ID. */
    unsigned int player_id;                         /*!< The ID of the player who has moved. */
    player_t player;                                /*!< The player information. */
    unsigned int take_extra;                        /*!< A boolean to know if the player take a extra. */


} TAckMovePacket ;

/**
 * @brief The constructor for create a TAckMovePacket object.
 *
 * @return A memory allocated object of the packet.
 */
TAckMovePacket *New_TAckMovePacket(unsigned char *raw);

/**
 * @brief Method to serialize the packet into a low-level buffer.
 *
 * @param this A pointer to the packet object.
 * @return Returns the low-level buffer length.
 *
 * You do not have to call this method directly. You must use the
 * Serialize method of the TAckMovePacket structure like this:
 * my_packet->Serialize(my_packet);
 */
int TAckMovePacket_Serialize(TAckMovePacket *this);

/**
 * @brief Method to de-serialize the low-level buffer into the packet.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Unserialize method of the TAckMovePacket structure like this:
 * my_packet->Unserialize(my_packet);
 */
void TAckMovePacket_Unserialize(TAckMovePacket *this);

/**
 * @brief Method to free the resource take by the object.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TAckMovePacket structure like this:
 * my_packet->Free(my_packet);
 */
void TAckMovePacket_New_Free(TAckMovePacket *this);

#endif

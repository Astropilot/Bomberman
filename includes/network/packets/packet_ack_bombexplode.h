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
 * @file network/packets/packet_ack_bombexplode.h
 * @brief Header file of the TAckBombExplodePacket class.
 *
 * The TAckBombExplodePacket class is a high-level packet.
 *
 */

#ifndef PACKET_ACK_BOMBEXPLODE_H_
#define PACKET_ACK_BOMBEXPLODE_H_

#include "core/map.h"
#include "core/bomb.h"
#include "core/utils.h"

/**
 * @brief An class representing the server response bomb explode packet.
 *
 * TAckBombExplodePacket is a class representing the server response bomb explode packet.
 */
typedef struct TAckBombExplodePacket {

    int(*Serialize)(struct TAckBombExplodePacket*);     /*!< Method to serialize the high-level packet. */

    void(*Unserialize)(struct TAckBombExplodePacket*);  /*!< Method to de-serialize the high-level packet. */

    void(*Free)(struct TAckBombExplodePacket*);         /*!< Free (ressources) method. */

    unsigned char *raw_packet;                          /*!< The low-leve buffer when packet is serialized. */
    int packet_id;                                      /*!< The packet ID. */
    bomb_t bomb;                                        /*!< The bomb that exploded. */
    unsigned int destroyed_count;                       /*!< The number of walls destroyed. */
    object_t *destroyed_blocks;                         /*!< The list of the destroyed blocks. */
    unsigned int flames_count;                          /*!< The number of flames. */
    pos_t *flames_blocks;                               /*!< The list of the flames. */
    unsigned int extra_count;                           /*!< The number of extra created. */
    object_t *extra_blocks;                             /*!< The list of the created extra. */

} TAckBombExplodePacket ;

/**
 * @fn TAckBombExplodePacket *New_TAckBombExplodePacket(unsigned char *raw)
 * @brief The constructor for create a TAckBombExplodePacket object.
 *
 * @return A memory allocated object of the packet.
 */
TAckBombExplodePacket *New_TAckBombExplodePacket(unsigned char *raw);

/**
 * @fn int TAckBombExplodePacket_Serialize(TAckBombExplodePacket *this)
 * @brief Method to serialize the packet into a low-level buffer.
 *
 * @param this A pointer to the packet object.
 * @return Returns the low-level buffer length.
 *
 * You do not have to call this method directly. You must use the
 * Serialize method of the TAckBombExplodePacket structure like this:
 * my_packet->Serialize(my_packet);
 */
int TAckBombExplodePacket_Serialize(TAckBombExplodePacket *this);

/**
 * @fn void TAckBombExplodePacket_Unserialize(TAckBombExplodePacket *this)
 * @brief Method to de-serialize the low-level buffer into the packet.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Unserialize method of the TAckBombExplodePacket structure like this:
 * my_packet->Unserialize(my_packet);
 */
void TAckBombExplodePacket_Unserialize(TAckBombExplodePacket *this);

/**
 * @fn void TAckBombExplodePacket_New_Free(TAckBombExplodePacket *this)
 * @brief Method to free the resource take by the object.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TAckBombExplodePacket structure like this:
 * my_packet->Free(my_packet);
 */
void TAckBombExplodePacket_New_Free(TAckBombExplodePacket *this);

#endif

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
 * @file network/packets/packet_ack_gameinit.h
 * @brief Header file of the TAckGameInitPacket class.
 *
 * The TAckGameInitPacket class is a high-level packet.
 *
 */

#ifndef PACKET_ACK_GAMEINIT_H_
#define PACKET_ACK_GAMEINIT_H_

#include "core/player.h"
#include "core/map.h"

/**
 * @brief An class representing the server response game init packet.
 *
 * TAckGameInitPacket is a class representing the server response game init packet.
 */
typedef struct TAckGameInitPacket {

    int(*Serialize)(struct TAckGameInitPacket*);    /*!< Method to serialize the high-level packet. */

    void(*Unserialize)(struct TAckGameInitPacket*); /*!< Method to de-serialize the high-level packet. */

    void(*Free)(struct TAckGameInitPacket*);        /*!< Free (ressources) method. */

    unsigned char *raw_packet;                      /*!< The low-leve buffer when packet is serialized. */
    int packet_id;                                  /*!< The packet ID. */
    unsigned int nb_players;                        /*!< The number of players in the game. */
    player_t *players;                              /*!< The list of players. */
    object_type_t **block_map;                      /*!< The new map generated. */


} TAckGameInitPacket ;

/**
 * @fn TAckGameInitPacket *New_TAckGameInitPacket(unsigned char *raw)
 * @brief The constructor for create a TAckGameInitPacket object.
 *
 * @return A memory allocated object of the packet.
 */
TAckGameInitPacket *New_TAckGameInitPacket(unsigned char *raw);

/**
 * @fn int TAckGameInitPacket_Serialize(TAckGameInitPacket *this)
 * @brief Method to serialize the packet into a low-level buffer.
 *
 * @param this A pointer to the packet object.
 * @return Returns the low-level buffer length.
 *
 * You do not have to call this method directly. You must use the
 * Serialize method of the TAckGameInitPacket structure like this:
 * my_packet->Serialize(my_packet);
 */
int TAckGameInitPacket_Serialize(TAckGameInitPacket *this);

/**
 * @fn void TAckGameInitPacket_Unserialize(TAckGameInitPacket *this)
 * @brief Method to de-serialize the low-level buffer into the packet.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Unserialize method of the TAckGameInitPacket structure like this:
 * my_packet->Unserialize(my_packet);
 */
void TAckGameInitPacket_Unserialize(TAckGameInitPacket *this);

/**
 * @fn void TAckGameInitPacket_New_Free(TAckGameInitPacket *this)
 * @brief Method to free the resource take by the object.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TAckGameInitPacket structure like this:
 * my_packet->Free(my_packet);
 */
void TAckGameInitPacket_New_Free(TAckGameInitPacket *this);

#endif

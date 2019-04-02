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
 * @file network/packets/packet_ack_endgame.h
 * @brief Header file of the TAckEndGamePacket class.
 *
 * The TAckEndGamePacket class is a high-level packet.
 *
 */

#ifndef PACKET_ACK_ENDGAME_H_
#define PACKET_ACK_ENDGAME_H_

#include "core/player.h"

/**
 * @brief Constants of the possible game results.
 *
 * game_result_t is a series of predefined constants for the different
 * game results.
 */
typedef enum game_result_t {
    WINNER,                 /*!< The game have a winner. */
    DRAW                    /*!< The game do not have a winner. */
} game_result_t ;

/**
 * @brief An class representing the server response end game packet.
 *
 * TAckEndGamePacket is a class representing the server response end game packet.
 */
typedef struct TAckEndGamePacket {

    int(*Serialize)(struct TAckEndGamePacket*);     /*!< Method to serialize the high-level packet. */

    void(*Unserialize)(struct TAckEndGamePacket*);  /*!< Method to de-serialize the high-level packet. */

    void(*Free)(struct TAckEndGamePacket*);         /*!< Free (ressources) method. */

    unsigned char *raw_packet;                      /*!< The low-leve buffer when packet is serialized. */
    int packet_id;                                  /*!< The packet ID. */
    unsigned int game_result;                       /*!< The game result (game_result_t). */
    player_t *winner;                               /*!< The winner or NULL if no winner. */

} TAckEndGamePacket ;

/**
 * @fn TAckEndGamePacket *New_TAckEndGamePacket(unsigned char *raw)
 * @brief The constructor for create a TAckEndGamePacket object.
 *
 * @return A memory allocated object of the packet.
 */
TAckEndGamePacket *New_TAckEndGamePacket(unsigned char *raw);

/**
 * @fn int TAckEndGamePacket_Serialize(TAckEndGamePacket *this)
 * @brief Method to serialize the packet into a low-level buffer.
 *
 * @param this A pointer to the packet object.
 * @return Returns the low-level buffer length.
 *
 * You do not have to call this method directly. You must use the
 * Serialize method of the TAckEndGamePacket structure like this:
 * my_packet->Serialize(my_packet);
 */
int TAckEndGamePacket_Serialize(TAckEndGamePacket *this);

/**
 * @fn void TAckEndGamePacket_Unserialize(TAckEndGamePacket *this)
 * @brief Method to de-serialize the low-level buffer into the packet.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Unserialize method of the TAckEndGamePacket structure like this:
 * my_packet->Unserialize(my_packet);
 */
void TAckEndGamePacket_Unserialize(TAckEndGamePacket *this);

/**
 * @fn void TAckEndGamePacket_New_Free(TAckEndGamePacket *this)
 * @brief Method to free the resource take by the object.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TAckEndGamePacket structure like this:
 * my_packet->Free(my_packet);
 */
void TAckEndGamePacket_New_Free(TAckEndGamePacket *this);

#endif

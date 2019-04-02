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
 * @file network/packets/packet_ack_startgame.h
 * @brief Header file of the TAckStartGamePacket class.
 *
 * The TAckStartGamePacket class is a high-level packet.
 *
 */

#ifndef PACKET_ACK_STARTGAME_H_
#define PACKET_ACK_STARTGAME_H_

/**
 * @brief An class representing the server response start game packet.
 *
 * TAckStartGamePacket is a class representing the server response start game packet.
 */
typedef struct TAckStartGamePacket {

    int(*Serialize)(struct TAckStartGamePacket*);       /*!< Method to serialize the high-level packet. */

    void(*Unserialize)(struct TAckStartGamePacket*);    /*!< Method to de-serialize the high-level packet. */

    void(*Free)(struct TAckStartGamePacket*);           /*!< Free (ressources) method. */

    unsigned char *raw_packet;                          /*!< The low-leve buffer when packet is serialized. */
    int packet_id;                                      /*!< The packet ID. */

} TAckStartGamePacket ;

/**
 * @fn TAckStartGamePacket *New_TAckStartGamePacket(unsigned char *raw)
 * @brief The constructor for create a TAckStartGamePacket object.
 *
 * @return A memory allocated object of the packet.
 */
TAckStartGamePacket *New_TAckStartGamePacket(unsigned char *raw);

/**
 * @fn int TAckStartGamePacket_Serialize(TAckStartGamePacket *this)
 * @brief Method to serialize the packet into a low-level buffer.
 *
 * @param this A pointer to the packet object.
 * @return Returns the low-level buffer length.
 *
 * You do not have to call this method directly. You must use the
 * Serialize method of the TAckStartGamePacket structure like this:
 * my_packet->Serialize(my_packet);
 */
int TAckStartGamePacket_Serialize(TAckStartGamePacket *this);

/**
 * @fn void TAckStartGamePacket_Unserialize(TAckStartGamePacket *this)
 * @brief Method to de-serialize the low-level buffer into the packet.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Unserialize method of the TAckStartGamePacket structure like this:
 * my_packet->Unserialize(my_packet);
 */
void TAckStartGamePacket_Unserialize(TAckStartGamePacket *this);

/**
 * @fn void TAckStartGamePacket_New_Free(TAckStartGamePacket *this)
 * @brief Method to free the resource take by the object.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TAckStartGamePacket structure like this:
 * my_packet->Free(my_packet);
 */
void TAckStartGamePacket_New_Free(TAckStartGamePacket *this);

#endif

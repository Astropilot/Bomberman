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
 * @file packet_ack_connect.h
 * @brief Header file of the TAckConnectPacket class.
 *
 * The TAckConnectPacket class is a high-level packet.
 *
 */

#ifndef PACKET_ACK_CONNECT_H_
#define PACKET_ACK_CONNECT_H_

/**
 * @brief Constants of the possible status when a player try to connect to server.
 *
 * connect_status_t is a series of predefined constants for the different
 * possible status when a player try to connect to server.
 */
typedef enum connect_status_t {
    OK,                 /*!< The player is connected. */
    GAME_FULL,          /*!< The game is full. */
    GAME_STARTED,       /*!< The game is already started. */
    UNDEFINED           /*!< Unknow error. */
} connect_status_t ;

/**
 * @brief An class representing the server response connect packet.
 *
 * TAckConnectPacket is a class representing the server response connect packet.
 */
typedef struct TAckConnectPacket {

    int(*Serialize)(struct TAckConnectPacket*);     /*!< Method to serialize the high-level packet. */

    void(*Unserialize)(struct TAckConnectPacket*);  /*!< Method to de-serialize the high-level packet. */

    void(*Free)(struct TAckConnectPacket*);         /*!< Free (ressources) method. */

    unsigned char *raw_packet;                      /*!< The low-leve buffer when packet is serialized. */
    int packet_id;                                  /*!< The packet ID. */
    int status;                                     /*!< The status of the connection. */
    unsigned int player;                            /*!< The new player ID of the player if connection if a success. */

} TAckConnectPacket ;

/**
 * @fn TAckConnectPacket *New_TAckConnectPacket(unsigned char *raw)
 * @brief The constructor for create a TAckConnectPacket object.
 *
 * @return A memory allocated object of the packet.
 */
TAckConnectPacket *New_TAckConnectPacket(unsigned char *raw);

/**
 * @fn int TAckConnectPacket_Serialize(TAckConnectPacket *this)
 * @brief Method to serialize the packet into a low-level buffer.
 *
 * @param this A pointer to the packet object.
 * @return Returns the low-level buffer length.
 *
 * You do not have to call this method directly. You must use the
 * Serialize method of the TAckConnectPacket structure like this:
 * my_packet->Serialize(my_packet);
 */
int TAckConnectPacket_Serialize(TAckConnectPacket *this);

/**
 * @fn void TAckConnectPacket_Unserialize(TAckConnectPacket *this)
 * @brief Method to de-serialize the low-level buffer into the packet.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Unserialize method of the TAckConnectPacket structure like this:
 * my_packet->Unserialize(my_packet);
 */
void TAckConnectPacket_Unserialize(TAckConnectPacket *this);

/**
 * @fn void TAckConnectPacket_New_Free(TAckConnectPacket *this)
 * @brief Method to free the resource take by the object.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TAckConnectPacket structure like this:
 * my_packet->Free(my_packet);
 */
void TAckConnectPacket_New_Free(TAckConnectPacket *this);

#endif

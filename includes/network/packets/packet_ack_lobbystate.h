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
 * @file network/packets/packet_ack_lobbystate.h
 * @brief Header file of the TAckLobbyStatePacket class.
 *
 * The TAckLobbyStatePacket class is a high-level packet.
 *
 */

#ifndef PACKET_ACK_LOBBYSTATE_H_
#define PACKET_ACK_LOBBYSTATE_H_

/**
 * @brief An class representing the server response lobby state packet.
 *
 * TAckLobbyStatePacket is a class representing the server response lobby state packet.
 */
typedef struct TAckLobbyStatePacket {

    int(*Serialize)(struct TAckLobbyStatePacket*);      /*!< Method to serialize the high-level packet. */

    void(*Unserialize)(struct TAckLobbyStatePacket*);   /*!< Method to de-serialize the high-level packet. */

    void(*Free)(struct TAckLobbyStatePacket*);          /*!< Free (ressources) method. */

    unsigned char *raw_packet;                          /*!< The low-leve buffer when packet is serialized. */
    int packet_id;                                      /*!< The packet ID. */
    unsigned int nb_players;                            /*!< The actual number of player in the lobby. */

} TAckLobbyStatePacket ;

/**
 * @brief The constructor for create a TAckLobbyStatePacket object.
 *
 * @return A memory allocated object of the packet.
 */
TAckLobbyStatePacket *New_TAckLobbyStatePacket(unsigned char *raw);

/**
 * @brief Method to serialize the packet into a low-level buffer.
 *
 * @param this A pointer to the packet object.
 * @return Returns the low-level buffer length.
 *
 * You do not have to call this method directly. You must use the
 * Serialize method of the TAckLobbyStatePacket structure like this:
 * my_packet->Serialize(my_packet);
 */
int TAckLobbyStatePacket_Serialize(TAckLobbyStatePacket *this);

/**
 * @brief Method to de-serialize the low-level buffer into the packet.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Unserialize method of the TAckLobbyStatePacket structure like this:
 * my_packet->Unserialize(my_packet);
 */
void TAckLobbyStatePacket_Unserialize(TAckLobbyStatePacket *this);

/**
 * @brief Method to free the resource take by the object.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TAckLobbyStatePacket structure like this:
 * my_packet->Free(my_packet);
 */
void TAckLobbyStatePacket_New_Free(TAckLobbyStatePacket *this);

#endif

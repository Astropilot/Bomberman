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
 * @file network/packets/packet_disconnect.h
 * @brief Header file of the TReqDisconnectPacket & TAckDisconnectPacket classes.
 *
 * The TReqDisconnectPacket & TAckDisconnectPacket classes are high-level packets.
 *
 */

#ifndef PACKET_DISCONNECT_H_
#define PACKET_DISCONNECT_H_

/**
 * @brief Constants of the disconnect reasons.
 *
 * leave_reason_t is a series of predefined constants for the different
 * disconnect reasons.
 */
typedef enum leave_reason_t {
    USER_QUIT,
    MASTER_LEAVE
} leave_reason_t ;

/**
 * @brief An class representing the client request disconnect packet.
 *
 * TReqDisconnectPacket is a class representing the client request disconnect packet.
 */
typedef struct TReqDisconnectPacket {

    int(*Serialize)(struct TReqDisconnectPacket*);      /*!< Method to serialize the high-level packet. */

    void(*Unserialize)(struct TReqDisconnectPacket*);   /*!< Method to de-serialize the high-level packet. */

    void(*Free)(struct TReqDisconnectPacket*);          /*!< Free (ressources) method. */

    unsigned char *raw_packet;                          /*!< The low-leve buffer when packet is serialized. */
    int packet_id;                                      /*!< The packet ID. */
    int reason;                                         /*!< The disconnect reason. */
    unsigned int player;                                /*!< The player ID who want to disconnect. */

} TReqDisconnectPacket ;

/**
 * @brief An class representing the server response disconnect packet.
 *
 * TAckDisconnectPacket is a class representing the server response disconnect packet.
 */
typedef struct TAckDisconnectPacket {

    int(*Serialize)(struct TAckDisconnectPacket*);      /*!< Method to serialize the high-level packet. */

    void(*Unserialize)(struct TAckDisconnectPacket*);   /*!< Method to de-serialize the high-level packet. */

    void(*Free)(struct TAckDisconnectPacket*);          /*!< Free (ressources) method. */

    unsigned char *raw_packet;                          /*!< The low-leve buffer when packet is serialized. */
    int packet_id;                                      /*!< The packet ID. */
    int reason;                                         /*!< The disconnect reason. */

} TAckDisconnectPacket ;

/**
 * @brief The constructor for create a TReqDisconnectPacket object.
 *
 * @return A memory allocated object of the packet.
 */
TReqDisconnectPacket *New_TReqDisconnectPacket(unsigned char *raw);

/**
 * @brief Method to serialize the packet into a low-level buffer.
 *
 * @param this A pointer to the packet object.
 * @return Returns the low-level buffer length.
 *
 * You do not have to call this method directly. You must use the
 * Serialize method of the TReqDisconnectPacket structure like this:
 * my_packet->Serialize(my_packet);
 */
int TReqDisconnectPacket_Serialize(TReqDisconnectPacket *this);

/**
 * @brief Method to de-serialize the low-level buffer into the packet.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Unserialize method of the TReqDisconnectPacket structure like this:
 * my_packet->Unserialize(my_packet);
 */
void TReqDisconnectPacket_Unserialize(TReqDisconnectPacket *this);

/**
 * @brief Method to free the resource take by the object.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TReqDisconnectPacket structure like this:
 * my_packet->Free(my_packet);
 */
void TReqDisconnectPacket_New_Free(TReqDisconnectPacket *this);

/**
 * @brief The constructor for create a TAckDisconnectPacket object.
 *
 * @return A memory allocated object of the packet.
 */
TAckDisconnectPacket *New_TAckDisconnectPacket(unsigned char *raw);

/**
 * @brief Method to serialize the packet into a low-level buffer.
 *
 * @param this A pointer to the packet object.
 * @return Returns the low-level buffer length.
 *
 * You do not have to call this method directly. You must use the
 * Serialize method of the TAckDisconnectPacket structure like this:
 * my_packet->Serialize(my_packet);
 */
int TAckDisconnectPacket_Serialize(TAckDisconnectPacket *this);

/**
 * @brief Method to de-serialize the low-level buffer into the packet.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Unserialize method of the TAckDisconnectPacket structure like this:
 * my_packet->Unserialize(my_packet);
 */
void TAckDisconnectPacket_Unserialize(TAckDisconnectPacket *this);

/**
 * @brief Method to free the resource take by the object.
 *
 * @param this A pointer to the packet object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TAckDisconnectPacket structure like this:
 * my_packet->Free(my_packet);
 */
void TAckDisconnectPacket_New_Free(TAckDisconnectPacket *this);

#endif

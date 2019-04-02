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
 * @file network/packets/packet.h
 * @brief Header file of the TPacket class.
 *
 * The TPacket mother class is a high-level packet which is inherited
 * by all the other packets.
 *
 */

#ifndef NETWORK_PACKET_H_
#define NETWORK_PACKET_H_

#include "network/network.h"

/**
 * @brief Constants of all packets ID.
 *
 * packet_t is a series of predefined constants for the different
 * packets ID
 */
typedef enum packet_t {
    REQ_CONNECT       = 0x01,
    REQ_DISCONNECT    = 0x02,
    REQ_START_GAME    = 0x03,
    REQ_PLACE_BOMB    = 0x04,
    REQ_MOVE          = 0x05,
    REQ_READY         = 0x06,

    ACK_CONNECT       = 0x07,
    ACK_DISCONNECT    = 0x08,
    ACK_LOBBY_STATE   = 0x09,
    ACK_START_GAME    = 0x0A,
    ACK_GAME_INIT     = 0x0B,
    ACK_MOVE          = 0x0C,
    ACK_PLACE_BOMB    = 0x0D,
    ACK_BOMB_EXPLODE  = 0x0E,
    ACK_PLAYER_UPDATE = 0x0F,
    ACK_END_GAME      = 0x10
} packet_t;

/**
 * @brief An class representing a generic packet.
 *
 * TPacket is a class representing a generic packet.
 */
typedef struct TPacket {

    int(*Serialize)(struct TPacket*);       /*!< Method to serialize the high-level packet. */

    void(*Unserialize)(struct TPacket*);    /*!< Method to de-serialize the high-level packet. */

    void(*Free)(struct TPacket*);           /*!< Free (ressources) method. */

    unsigned char *raw_packet;              /*!< The low-leve buffer when packet is serialized. */

} TPacket ;

/**
 * @fn int extract_packet_id(unsigned char *raw_packet)
 * @brief Method to extract the packet ID (type) from a raw low-level buffer.
 *
 * @param raw_packet The low-level buffer of the packet.
 * @return Returns the packet ID found in the buffer.
 */
int extract_packet_id(unsigned char *raw_packet);

/**
 * @fn TMessage packet_to_message(TPacket *packet, unsigned int auto_free)
 * @brief Method convert a generic packet into a TMessage object.
 *
 * @param packet The packet to convert.
 * @param auto_free A boolean to know if the packet need to be free after conversion.
 * @return Returns the TMessage converted object.
 */
TMessage packet_to_message(TPacket *packet, unsigned int auto_free);

#endif

/*******************************************************************************
* PROJECT: gLib
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
 * @file message.h
 * @brief Header file of the message class of gLib.
 *
 * This class allows you to create and manipulate high-level messages.
 *
 */

#ifndef GLIB_MESSAGE_H_
#define GLIB_MESSAGE_H_

/**
 * @brief Object oriented structure representing a high-level message.
 *
 * TMessage is an object that allows you to create a high-level message.
 */
typedef struct TMessage {

    int len;                        /*!< The length of the message. */
    unsigned char *message;         /*!< The raw packet bytes of the message. */

} TMessage ;

#endif

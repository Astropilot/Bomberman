/*
** ETNA PROJECT, 05/02/2019 by martin_h, hamide_a, despla_g, weber_w
** resLib
** File description:
**      Wrapper around the socket API.
*/

/**
 * @file message.h
 * @brief Header file of the message class of ResLib.
 * @author Yohann.M, Gauthier.D, Aziz.H, William.W
 * @version 1.0
 * @date 28 janvier 2019
 *
 * This class allows you to create and manipulate high-level messages.
 *
 */

#ifndef RESLIB_MESSAGE_H_
#define RESLIB_MESSAGE_H_

#include <stdlib.h>

/**
 * @struct TMessage
 * @brief Object oriented structure representing a high-level message.
 *
 * TMessage is an object that allows you to create a high-level message.
 */
typedef struct {

    int len;                        /*!< The length of the message. */
    unsigned char *message;         /*!< The raw packet bytes of the message. */

} TMessage ;

#endif

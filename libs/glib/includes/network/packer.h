/*
** ETNA PROJECT, 05/02/2019 by martin_h, hamide_a, despla_g, weber_w
** resLib
** File description:
**      Wrapper around the socket API.
*/

/**
 * @file packer.h
 * @brief Header file of utils funtions for creating advanded packets.
 * @author Yohann.M, Gauthier.D, Aziz.H, William.W
 * @version 1.0
 * @date 28 janvier 2019
 *
 * This file provide a lot of functions for creating advanded packets.
 *
 */

#ifndef GLIB_PACKER_H_
#define GLIB_PACKER_H_

/**
 * @fn unsigned char *pack_int(unsigned char *buffer, int i)
 * @brief Transform and add an integer to an unsigned char buffer.
 *
 * @param buffer The buffer that will receive the integer.
 * @param i The integer to add.
 * @return The address of the buffer after the integer added.
 *
 */
unsigned char *pack_int(unsigned char *buffer, int i);

/**
 * @fn unsigned char *unpack_int(unsigned char *buffer, int *i)
 * @brief Extract an integer from a unsigned char buffer.
 *
 * @param buffer The buffer that contains the integer.
 * @param i An pointer to the integer that will be extracted.
 * @return The address of the buffer after the integer extracted.
 *
 */
unsigned char *unpack_int(unsigned char *buffer, int *i);

/**
 * @fn unsigned char *pack_uint(unsigned char *buffer, unsigned int ui)
 * @brief Transform and add an unsigned integer to an unsigned char buffer.
 *
 * @param buffer The buffer that will receive the unsigned integer.
 * @param ui The unsigned integer to add.
 * @return The address of the buffer after the unsigned integer added.
 *
 */
unsigned char *pack_uint(unsigned char *buffer, unsigned int ui);

/**
 * @fn unsigned char *unpack_uint(unsigned char *buffer, unsigned int *ui)
 * @brief Extract an unsigned integer from a unsigned char buffer.
 *
 * @param buffer The buffer that contains the unsigned integer.
 * @param ui An pointer to the unsigned integer that will be extracted.
 * @return The address of the buffer after the unsigned integer extracted.
 *
 */
unsigned char *unpack_uint(unsigned char *buffer, unsigned int *ui);

/**
 * @fn unsigned char *pack_char(unsigned char *buffer, char chr)
 * @brief Transform and add an char to an unsigned char buffer.
 *
 * @param buffer The buffer that will receive the char.
 * @param chr The char to add.
 * @return The address of the buffer after the char added.
 *
 */
unsigned char *pack_char(unsigned char *buffer, char chr);

/**
 * @fn unsigned char *unpack_char(unsigned char *buffer, char *chr)
 * @brief Extract an char from a unsigned char buffer.
 *
 * @param buffer The buffer that contains the char.
 * @param chr An pointer to the char that will be extracted.
 * @return The address of the buffer after the char extracted.
 *
 */
unsigned char *unpack_char(unsigned char *buffer, char *chr);

/**
 * @fn unsigned char *pack_string(unsigned char *buffer, const char *str)
 * @brief Transform and add an char array to an unsigned char buffer.
 *
 * @param buffer The buffer that will receive the char array.
 * @param str The char array to add.
 * @return The address of the buffer after the char array added.
 *
 */
unsigned char *pack_string(unsigned char *buffer, const char *str);

/**
 * @fn unsigned char *unpack_string(unsigned char *buffer, char *str)
 * @brief Extract an char array from a unsigned char buffer.
 *
 * @param buffer The buffer that contains the char array.
 * @param str An pointer to the char array that will be extracted.
 * @return The address of the buffer after the char array extracted.
 *
 */
unsigned char *unpack_string(unsigned char *buffer, char *str);

#endif

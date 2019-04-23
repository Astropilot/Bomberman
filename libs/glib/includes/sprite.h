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
 * @file sprite.h
 * @brief Header file of the sprite component of GLib.
 *
 * The sprite component allows you to create a graphical sprite with
 * one frame (static) that can be manipulated by GLib.
 *
 */

#ifndef GLIB_SPRITE_H_
#define GLIB_SPRITE_H_

#include <SDL2/SDL.h>

typedef struct TScene TScene;

/**
 * @brief Object oriented structure representing a sprite.
 *
 * TSprite is an object that allows you to create and display a sprite.
 */
typedef struct TSprite {

    void(*Draw)(struct TSprite*, TScene*);          /*!< Draw method. */

    void(*Free)(struct TSprite*);                   /*!< Free (ressources) method. */

    unsigned int is_visible;                        /*!< Boolean to know if the drawable can be drawed automatically. */
    SDL_Texture *texture;                           /*!< The SDL texture of the sprite. */
    SDL_Rect pos;                                   /*!< The position of the sprite. */
    char *file;                                     /*!< The image file path of the sprite. */

} TSprite ;

/**
 * @brief The constructor for create a TSprite object.
 *
 * @param scene A pointer to the scene object.
 * @param file A image file path for the sprite.
 * @param pos The position of the sprite on the screen.
 * @return A memory allocated object of the sprite.
 */
TSprite* New_TSprite(TScene *scene, const char *file, SDL_Rect pos);

/**
 * @brief Method for drawing the sprite in the interface.
 *
 * @param this A pointer to the sprite object to draw.
 * @param scene A pointer to the scene object.
 *
 * You do not have to call this method directly. You must use the
 * Draw method of the TSprite structure like this:
 * my_sprite->Draw(my_sprite, scene);
 */
void TSprite_Draw(TSprite *this, TScene *scene);

/**
 * @brief Method to free all ressources take by the sprite.
 *
 * @param this A pointer to the sprite object to free.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TSprite structure like this:
 * my_sprite->Free(my_sprite);
 */
void TSprite_New_Free(TSprite *this);

#endif

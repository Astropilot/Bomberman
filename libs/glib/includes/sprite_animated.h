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
 * @file sprite_animated.h
 * @brief Header file of the animated sprite component of GLib.
 *
 * The animated sprite component allows you to create a graphical animated
 * sprite that can be manipulated by GLib.
 *
 */

#ifndef GLIB_SPRITE_ANIMATED_H_
#define GLIB_SPRITE_ANIMATED_H_

#include <SDL2/SDL.h>

typedef struct TScene TScene;

/**
 * @brief Object oriented structure representing a animated sprite.
 *
 * TAnimatedSprite is an object that allows you to create and display a animated sprite.
 */
typedef struct TAnimatedSprite {

    void(*Draw)(struct TAnimatedSprite*, TScene*);      /*!< Draw method. */

    void(*Free)(struct TAnimatedSprite*);               /*!< Free (ressources) method. */

    unsigned int is_visible;                            /*!< Boolean to know if the drawable can be drawed automatically. */

    SDL_Texture *texture;                               /*!< The texture with all frames of the sprite. */
    SDL_Rect size;                                      /*!< The size of a single frame. */
    SDL_Rect pos;                                       /*!< The size and position of the animated sprite on the screen. */
    char *file;                                         /*!< The image file of the sprite. */
    size_t speed;                                       /*!< The delay in milliseconds between each frame. */
    size_t len_frames;                                  /*!< The number of frames, automatically calculated. */
    unsigned int actual_frame;                          /*!< The actual index frame to draw. */
    unsigned int last_time;                             /*!< Internal variable for sprite animation timing */
    int animations;                                     /*!< The number of animations. */

} TAnimatedSprite ;

/**
 * @brief The constructor for create a TAnimatedSprite object.
 *
 * @param scene A pointer to the scene object.
 * @param file The path of an image file containing all the sprite frames.
 * @param size The size of a single frame, the x and y are ignored.
 * @param pos The position and size of the sprite on the screen.
 * @param speed The delay in milliseconds between each frame.
 * @param animations The number of animations, can be -1 for infinite loop.
 * @return A memory allocated object of the animated sprite.
 */
TAnimatedSprite* New_TAnimatedSprite(TScene *scene, const char *file, SDL_Rect size, SDL_Rect pos, size_t speed, int animations);

/**
 * @brief Method for drawing the animated sprite in the interface.
 *
 * @param this A pointer to the animated sprite object to draw.
 * @param scene A pointer to the scene object.
 *
 * You do not have to call this method directly. You must use the
 * Draw method of the TAnimatedSprite structure like this:
 * my_sprite->Draw(my_sprite, scene);
 */
void TAnimatedSprite_Draw(TAnimatedSprite *this, TScene *scene);

/**
 * @brief Method to free all ressources take by the animated sprite.
 *
 * @param this A pointer to the animated sprite object to free.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TAnimatedSprite structure like this:
 * my_sprite->Free(my_sprite);
 */
void TAnimatedSprite_New_Free(TAnimatedSprite *this);

#endif

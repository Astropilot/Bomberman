/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Header file of the animated sprite component of GLib.
*/

/**
 * @file sprite_animated.h
 * @brief Header file of the animated sprite component of GLib.
 * @author Yohann.M, Gauthier.D, Aziz.H, William.W
 * @version 1.0
 * @date 28 janvier 2019
 *
 * The animated sprite component allows you to create a graphical animated
 * sprite that can be manipulated by GLib.
 *
 */

#ifndef GLIB_SPRITE_ANIMATED_H_
#define GLIB_SPRITE_ANIMATED_H_

#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct TFrame TFrame;

/**
 * @struct TAnimatedSprite
 * @brief Object oriented structure representing a animated sprite.
 *
 * TAnimatedSprite is an object that allows you to create and display a animated sprite.
 */
typedef struct TAnimatedSprite {

    void(*Draw)(struct TAnimatedSprite*, TFrame*);      /*!< Draw method. */

    void(*Free)(struct TAnimatedSprite*);               /*!< Free (ressources) method. */

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
 * @fn TAnimatedSprite* New_TAnimatedSprite(TFrame *frame, const char *file, SDL_Rect size, SDL_Rect pos, size_t speed, int animations)
 * @brief The constructor for create a TAnimatedSprite object.
 *
 * @param frame A pointer to the frame object.
 * @param file The path of an image file containing all the sprite frames.
 * @param size The size of a single frame, the x and y are ignored.
 * @param pos The position and size of the sprite on the screen.
 * @param speed The delay in milliseconds between each frame.
 * @param animations The number of animations, can be -1 for infinite loop.
 * @return A memory allocated object of the animated sprite.
 */
TAnimatedSprite* New_TAnimatedSprite(TFrame *frame, const char *file, SDL_Rect size, SDL_Rect pos, size_t speed, int animations);

/**
 * @fn void TAnimatedSprite_Draw(TAnimatedSprite *this, TFrame *frame)
 * @brief Method for drawing the animated sprite in the interface.
 *
 * @param this A pointer to the animated sprite object to draw.
 * @param frame A pointer to the frame object.
 *
 * You do not have to call this method directly. You must use the
 * Draw method of the TAnimatedSprite structure like this:
 * my_sprite->Draw(my_sprite, frame);
 */
void TAnimatedSprite_Draw(TAnimatedSprite *this, TFrame *frame);

/**
 * @fn void TAnimatedSprite_New_Free(TAnimatedSprite *this)
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

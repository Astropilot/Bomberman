/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Header file of the animated sprites component of GLib.
*/

/**
 * @file sprite_animated.h
 * @brief Header file of the animated sprites component of GLib.
 * @author Yohann.M, Gauthier.D, Aziz.H, William.W
 * @version 1.0
 * @date 28 janvier 2019
 *
 * The animated sprites component allows you to create a graphical animated
 * sprite from multiple images that can be manipulated by GLib.
 *
 */

#ifndef GLIB_SPRITES_ANIMATED_H_
#define GLIB_SPRITES_ANIMATED_H_

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct TFrame TFrame;

/**
 * @brief Object oriented structure representing a animated sprite from multiple images..
 *
 * TAnimatedSprite is an object that allows you to create and display a animated sprite.
 */
typedef struct TAnimatedSprites {

    void(*Draw)(struct TAnimatedSprites*, TFrame*);     /*!< Draw method. */

    void(*Free)(struct TAnimatedSprites*);              /*!< Free (ressources) method. */

    unsigned int is_visible;                            /*!< Boolean to know if the drawable can be drawed automatically. */
    SDL_Rect size;                                      /*!< The size of a single image. */
    SDL_Rect pos;                                       /*!< The size and position of the animated sprites on the screen. */
    char *file_template;                                /*!< The image file template of the sprites. */
    size_t speed;                                       /*!< The delay in milliseconds between each frame. */
    size_t nb_images;                                   /*!< The number of images. */
    unsigned int actual_image;                          /*!< The actual index frame to draw. */
    unsigned int last_time;                             /*!< Internal variable for sprite animation timing */
    int animations;                                     /*!< The number of animations. */
    SDL_Texture **textures;                             /*!< The textures of the sprites. */

} TAnimatedSprites ;

/**
 * @fn TAnimatedSprites* New_TAnimatedSprites(TFrame *frame, const char *file_template, size_t files, SDL_Rect size, SDL_Rect pos, size_t speed, int animations)
 * @brief The constructor for create a TAnimatedSprites object.
 *
 * @param frame A pointer to the frame object.
 * @param file_template The template path of the image files containing all the sprite frames.
 * @param files The number of files.
 * @param size The size of a single frame, the x and y are ignored.
 * @param pos The position and size of the sprite on the screen.
 * @param speed The delay in milliseconds between each frame.
 * @param animations The number of animations, can be -1 for infinite loop.
 * @return A memory allocated object of the animated sprite.
 */
TAnimatedSprites* New_TAnimatedSprites(TFrame *frame, const char *file_template, size_t files, SDL_Rect size, SDL_Rect pos, size_t speed, int animations);

/**
 * @fn void TAnimatedSprites_Draw(TAnimatedSprites *this, TFrame *frame)
 * @brief Method for drawing the animated sprite in the interface.
 *
 * @param this A pointer to the animated sprite object to draw.
 * @param frame A pointer to the frame object.
 *
 * You do not have to call this method directly. You must use the
 * Draw method of the TAnimatedSprites structure like this:
 * my_sprite->Draw(my_sprite, frame);
 */
void TAnimatedSprites_Draw(TAnimatedSprites *this, TFrame *frame);

/**
 * @fn void TAnimatedSprites_New_Free(TAnimatedSprites *this)
 * @brief Method to free all ressources take by the animated sprite.
 *
 * @param this A pointer to the animated sprite object to free.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TAnimatedSprites structure like this:
 * my_sprite->Free(my_sprite);
 */
void TAnimatedSprites_New_Free(TAnimatedSprites *this);

#endif

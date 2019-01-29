/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Header file of the sprite component of GLib.
*/

/**
 * @file sprite.h
 * @brief Header file of the sprite component of GLib.
 * @author Yohann.M, Gauthier.D, Aziz.H, William.W
 * @version 1.0
 * @date 28 janvier 2019
 *
 * The sprite component allows you to create a graphical sprite with
 * one frame (static) that can be manipulated by GLib.
 *
 */

#ifndef GLIB_SPRITE_H_
#define GLIB_SPRITE_H_

#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct TWindow TWindow;

/**
 * @struct TSprite
 * @brief Object oriented structure representing a sprite.
 *
 * TSprite is an object that allows you to create and display a sprite.
 */
typedef struct TSprite {

    void(*Draw)(struct TSprite*, TWindow*);         /*!< Draw method. */

    void(*Free)(struct TSprite*);                   /*!< Free (ressources) method. */

    SDL_Texture *texture;                           /*!< The SDL texture of the sprite. */
    SDL_Rect pos;                                   /*!< The position of the sprite. */
    char *file;                                     /*!< The image file path of the sprite. */

} TSprite ;

/**
 * @fn TSprite* New_TSprite(TWindow *win, const char *file, SDL_Rect size)
 * @brief The constructor for create a TSprite object.
 *
 * @param win A pointer to the window object.
 * @param file A image file path for the sprite.
 * @param pos The position of the sprite on the screen.
 * @return A memory allocated object of the sprite.
 */
TSprite* New_TSprite(TWindow *win, const char *file, SDL_Rect pos);

/**
 * @fn void TSprite_Draw(TSprite *this, TWindow *win)
 * @brief Method for drawing the sprite in the interface.
 *
 * @param this A pointer to the sprite object to draw.
 * @param win A pointer to the window object.
 *
 * You do not have to call this method directly. You must use the
 * Draw method of the TSprite structure like this:
 * my_sprite->Draw(my_sprite, window);
 */
void TSprite_Draw(TSprite *this, TWindow *win);

/**
 * @fn void TSprite_New_Free(TSprite *this)
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

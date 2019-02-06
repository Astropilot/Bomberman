/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Header file of the drawables tools of GLib.
*/

/**
 * @file drawables.h
 * @brief Header file of the drawables tools of GLib.
 * @author Yohann.M, Gauthier.D, Aziz.H, William.W
 * @version 1.0
 * @date 28 janvier 2019
 *
 * The button component allows you to create a graphical button that can
 * be manipulated by GLib.
 *
 */

#ifndef GLIB_DRAWABLES_H_
#define GLIB_DRAWABLES_H_

#include <stdlib.h>
#include <unistd.h>

typedef struct TWindow TWindow;

/**
 * @enum drawables_e
 * @brief Constants of all the drawables type.
 *
 * drawables_e is a series of predefined constants for the different
 * types of drawable.
 */
typedef enum drawables_e {
    SPRITE,                 /*!< TSprite object type. */
    ANIMATED_SPRITE,        /*!< TAnimatedSprite object type. */
    ANIMATED_SPRITES,       /*!< TAnimatedSprites object type. */
    TEXT,                   /*!< TText object type. */
    BUTTON,                 /*!< TButton object type. */
    INPUT                   /*!< TInput object type. */
} drawables_e ;

/**
 * @struct Drawable_Node
 * @brief A linked list for generic drawables.
 *
 * Drawable_Node is an linked list for stock differents types of drawables.
 */
typedef struct Drawable_Node {
    char *id;                       /*!< An unique ID for each drawable. */
    unsigned int priority;          /*!< The drawing priority, the lower the priority (close to 1), the more it will be drawn last. */
    drawables_e type;               /*!< The drawable type. */
    void *drawable;                 /*!< The drawable object. */
    struct Drawable_Node *next;     /*!< A pointer to the next Drawable_Node. */
} Drawable_Node ;

/**
 * @fn void drawableCallDraw(Drawable_Node *drawable, TWindow *win)
 * @brief This function will call the Draw method of the drawable given.
 *
 * @param drawable A pointer to a drawable node (of the linked list).
 * @param win A pointer to the window object.
 */
void drawableCallDraw(Drawable_Node *drawable, TWindow *win);

/**
 * @fn void drawableCallFree(Drawable_Node *drawable)
 * @brief This function will call the Free method of the drawable given.
 *
 * @param drawable A pointer to a drawable node (of the linked list).
 */
void drawableCallFree(Drawable_Node *drawable);

#endif

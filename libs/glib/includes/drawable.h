/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Header file of the drawable abstract class of GLib.
*/

/**
 * @file drawable.h
 * @brief Header file of the drawable abstract class of GLib.
 * @author Yohann.M, Gauthier.D, Aziz.H, William.W
 * @version 1.0
 * @date 28 janvier 2019
 *
 * The drawable is the abstract mother class of all the graphical components.
 *
 */

#ifndef GLIB_DRAWABLES_H_
#define GLIB_DRAWABLES_H_

#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>

typedef struct TFrame TFrame;

/**
 * @struct TDrawable
 * @brief An abstract mother class for all the graphical components.
 *
 * Drawable_Node is an abstract mother class for all the graphical components.
 */
typedef struct {

    void(*Draw)(struct TDrawable*, TFrame*);                           /*!< Draw method. */

    void(*Free)(struct TDrawable*);                                    /*!< Free (ressources) method. */

} TDrawable ;

/**
 * @struct Drawable_Node
 * @brief A linked list for generic drawables.
 *
 * Drawable_Node is an linked list for stock differents types of drawables.
 */
typedef struct {
    char *id;                       /*!< An unique ID for each drawable. */
    unsigned int priority;          /*!< The drawing priority, the lower the priority (close to 1), the more it will be drawn last. */
    TDrawable *drawable;            /*!< The drawable object. */
    struct Drawable_Node *next;     /*!< A pointer to the next Drawable_Node. */
} Drawable_Node ;

#endif

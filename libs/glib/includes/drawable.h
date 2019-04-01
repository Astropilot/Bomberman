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
 * @file drawable.h
 * @brief Header file of the drawable abstract class of GLib.
 *
 * The drawable is the abstract mother class of all the graphical components.
 *
 */

#ifndef GLIB_DRAWABLES_H_
#define GLIB_DRAWABLES_H_

#include <SDL2/SDL.h>

typedef struct TFrame TFrame;

/**
 * @brief An abstract mother class for all the graphical components.
 *
 * TDrawable is an abstract mother class for all the graphical components.
 */
typedef struct TDrawable {

    void(*Draw)(struct TDrawable*, TFrame*);                           /*!< Draw method. */

    void(*Free)(struct TDrawable*);                                    /*!< Free (ressources) method. */

    unsigned int is_visible;                                           /*!< Boolean to know if the drawable can be drawed automatically. */

} TDrawable ;

/**
 * @brief A linked list for generic drawables.
 *
 * TDrawable_Node is an linked list for stock differents types of drawables.
 */
typedef struct TDrawable_Node {
    unsigned long id;               /*!< An unique ID for each drawable. */
    unsigned int priority;          /*!< The drawing priority, the lower the priority (close to 1), the more it will be drawn last. */
    unsigned int free_strategy;     /*!< The free strategy to use. */
    TDrawable *drawable;            /*!< The drawable object. */
    struct TDrawable_Node *next;    /*!< A pointer to the next TDrawable_Node. */
} TDrawable_Node ;

#endif

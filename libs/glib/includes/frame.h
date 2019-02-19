/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Header file of the TFrame of GLib.
*/

/**
 * @file frame.h
 * @brief Header file of the TFrame of GLib.
 * @author Yohann.M, Gauthier.D, Aziz.H, William.W
 * @version 1.0
 * @date 28 janvier 2019
 *
 * The TFrame object allow you to create an isolated graphic environnement
 * whith it own logic.
 *
 */

#ifndef GLIB_FRAME_H_
#define GLIB_FRAME_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "sprite.h"
#include "drawable.h"

typedef struct TWindow TWindow;

/**
 * @brief Object oriented structure representing a frame.
 *
 * TFrame is an object that allows you to create and define a new frame.
 */
typedef struct TFrame {

    void(*Add_Drawable)(struct TFrame*, TDrawable*, const char*, unsigned int);             /*!< Method for adding a drawable with an ID and a priority. */

    TDrawable*(*Remove_Drawable)(struct TFrame*, const char *id);                           /*!< Method for deleting a drawable by its ID. */

    TDrawable*(*Get_Drawable)(struct TFrame*, const char *id);                              /*!< Method for getting a drawable by its ID. */

    void(*Draw_Drawables)(struct TFrame*);                                                  /*!< Method for drawing all the drawables added. */

    void(*Init)(struct TFrame*);                                                            /*!< Method to be defined on the TFrame creation. Called one time on first show. */

    void(*On_Load)(struct TFrame*, int argc, va_list args);                                 /*!< Method to be defined on the TFrame creation. Called each time the frame is shown. */

    void(*On_Event)(struct TFrame*, SDL_Event);                                             /*!< Method to be defined on the TFrame creation. Called on each SDL event. */

    void(*On_Tick)(struct TFrame*);                                                         /*!< Method to be defined on the TFrame creation. Called on each tick in game loop */

    void(*On_Unload)(struct TFrame*);                                                       /*!< Method to be defined on the TFrame creation. Called each time the frame become invisible. */

    void(*Finish)(struct TFrame*);                                                          /*!< Method to be defined on the TFrame creation. Called one time at the end of the program. */

    void(*Free)(struct TFrame*);                                                            /*!< Method for free all TFrame ressources, include drawables. */

    TWindow *window;                                        /*!< The main window. */
    char *frame_id;                                         /*!< The ID of the frame. */
    unsigned int initialized;                               /*!< Boolean to know if the frame has been initialized or not. */
    TDrawable_Node *drawables_head;                          /*!< A linked list of drawables. */

} TFrame ;

/**
 * @brief A linked list node for frames.
 *
 * TFrame_Node is an linked list node for stock TFrame objects.
 */
typedef struct TFrame_Node{
    TFrame *frame;
    struct TFrame_Node *next;
} TFrame_Node ;

/**
 * @fn TFrame* New_TFrame(const char *frame_id)
 * @brief The constructor for create a TFrame object.
 *
 * @param frame_id A unique ID.
 * @return A memory allocated object of the frame.
 */
TFrame* New_TFrame(const char *frame_id);

/**
 * @fn void TFrame_Add_Drawable(TFrame *this, TDrawable *drawable, const char *id, unsigned int priority)
 * @brief Method for adding a drawable to the frame.
 *
 * @param this A pointer to the frame object.
 * @param drawable A generic drawable.
 * @param id An unique ID for the drawable.
 * @param priority The drawing priority. The lower the priority (close to 1), the more it will be drawn last.
 *
 * You do not have to call this method directly. You must use the
 * Add_Drawable method of the TFrame structure like this:
 * my_frame->Add_Drawable(my_frame, (TDrawable*)my_drawable, "MY_DRAWABLE", 1);
 */
void TFrame_Add_Drawable(TFrame *this, TDrawable *drawable, const char *id, unsigned int priority);

/**
 * @fn TDrawable *TFrame_Remove_Drawable(TFrame *this, const char *id)
 * @brief Method for deleting a drawable. The drawable is not free !
 *
 * @param this A pointer to the frame object.
 * @param id The ID of the drawable to delete.
 * @return The drawable object deleted from the frame.
 *
 * You do not have to call this method directly. You must use the
 * Add_Drawable method of the TFrame structure like this:
 * my_frame->Remove_Drawable(my_frame, "MY_DRAWABLE");
 */
TDrawable *TFrame_Remove_Drawable(TFrame *this, const char *id);

/**
 * @fn TDrawable *TFrame_Get_Drawable(TFrame *this, const char *id)
 * @brief Method for getting a drawable.
 *
 * @param this A pointer to the frame object.
 * @param id The ID of the drawable to get.
 * @return The drawable object.
 *
 * You do not have to call this method directly. You must use the
 * Get_Drawable method of the TFrame structure like this:
 * my_frame->Get_Drawable(my_frame, "MY_DRAWABLE");
 */
TDrawable *TFrame_Get_Drawable(TFrame *this, const char *id);

/**
 * @fn void TFrame_Draw_Drawables(TFrame *this)
 * @brief Method for drawing all drawables in the frame.
 *
 * @param this A pointer to the frame object.
 *
 * You do not have to call this method directly. You must use the
 * Draw_Drawables method of the TFrame structure like this:
 * my_frame->Draw_Drawables(my_frame);
 */
void TFrame_Draw_Drawables(TFrame *this);

/**
 * @fn void TFrame_New_Free(TFrame *this)
 * @brief Method to free all ressources take by the frame, drawables included.
 *
 * @param this A pointer to the frame object to free.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TFrame structure like this:
 * my_frame->Free(my_frame);
 */
void TFrame_New_Free(TFrame *this);

#endif

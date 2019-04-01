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
 * @file frame.h
 * @brief Header file of the TFrame of GLib.
 *
 * The TFrame object allow you to create an isolated graphic environnement
 * whith it own logic.
 *
 */

#ifndef GLIB_FRAME_H_
#define GLIB_FRAME_H_

#include <stdarg.h>

#include "drawable.h"

#define GLIB_NO_FREE 0          /*!< Flag for not free a resource at any moment. */
#define GLIB_FREE_ON_FINISH 1   /*!< Flag for free a resource when frame finished. */
#define GLIB_FREE_ON_UNLOAD 2   /*!< Flag for free a resource when frame unloaded. */

typedef struct TWindow TWindow;

/**
 * @brief Object oriented structure representing a frame.
 *
 * TFrame is an object that allows you to create and define a new frame.
 */
typedef struct TFrame {

    void(*Add_Drawable)(struct TFrame*, TDrawable*, const char*, unsigned int, unsigned int);/*!< Method for adding a drawable with an ID and a priority. */

    TDrawable*(*Remove_Drawable)(struct TFrame*, const char*);                              /*!< Method for deleting a drawable by its ID. */

    unsigned int(*Remove_Drawable_Obj)(struct TFrame*, TDrawable*);                         /*!< Method for deleting a drawable. */

    unsigned int(*Free_Drawable)(struct TFrame*, const char*);                              /*!< Method for deleting and freeing the first drawable found by its ID. */

    unsigned int(*Free_Drawable_Obj)(struct TFrame*, TDrawable*);                           /*!< Method for deleting and freeing a drawable. */

    unsigned int(*Free_Drawables)(struct TFrame*, const char*);                             /*!< Method for deleting and freeing all drawables that share the same ID. */

    TDrawable*(*Get_Drawable)(struct TFrame*, const char*);                                 /*!< Method for getting a drawable by its ID. */

    void(*Draw_Drawables)(struct TFrame*);                                                  /*!< Method for drawing all the drawables added. */

    void(*Free_All_Drawables)(struct TFrame*, unsigned int);                                /*!< Method for freeing all the drawable according to the free strategy given. */

    void(*Init)(struct TFrame*);                                                            /*!< Method to be defined on the TFrame creation. Called one time on first show. */

    void(*On_Load)(struct TFrame*, int, va_list);                                           /*!< Method to be defined on the TFrame creation. Called each time the frame is shown. */

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
typedef struct TFrame_Node {
    TFrame *frame;                  /*!< The frame object. */
    struct TFrame_Node *next;       /*!< A pointer to the next TFrame_Node. */
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
 * @fn void TFrame_Add_Drawable(TFrame *this, TDrawable *drawable, const char *id, unsigned int priority, unsigned int free_strategy)
 * @brief Method for adding a drawable to the frame.
 *
 * @param this A pointer to the frame object.
 * @param drawable A generic drawable.
 * @param id An unique ID for the drawable.
 * @param priority The drawing priority. The lower the priority (close to 1), the more it will be drawn last.
 * @param free_strategy The free strategy to use for this resource.
 *
 * You do not have to call this method directly. You must use the
 * Add_Drawable method of the TFrame structure like this:
 * my_frame->Add_Drawable(my_frame, (TDrawable*)my_drawable, "MY_DRAWABLE", 1, GLIB_FREE_ON_FINISH);
 */
void TFrame_Add_Drawable(TFrame *this, TDrawable *drawable, const char *id, unsigned int priority, unsigned int free_strategy);

/**
 * @fn TDrawable *TFrame_Remove_Drawable(TFrame *this, const char *id)
 * @brief Method for deleting a drawable. The drawable is not free !
 *
 * @param this A pointer to the frame object.
 * @param id The ID of the drawable to delete.
 * @return The drawable object deleted from the frame.
 *
 * You do not have to call this method directly. You must use the
 * Remove_Drawable method of the TFrame structure like this:
 * my_frame->Remove_Drawable(my_frame, "MY_DRAWABLE");
 */
TDrawable *TFrame_Remove_Drawable(TFrame *this, const char *id);

/**
 * @fn unsigned int TFrame_Remove_Drawable_Obj(TFrame *this, TDrawable *drawable)
 * @brief Method for deleting a drawable. The drawable is not free !
 *
 * @param this A pointer to the frame object.
 * @param drawable A pointer to the drawable object to remove.
 * @return Return 1 if an drawable has been deleted, 0 otherwise.
 *
 * You do not have to call this method directly. You must use the
 * Remove_Drawable_Obj method of the TFrame structure like this:
 * my_frame->Remove_Drawable_Obj(my_frame, my_drawable);
 */
unsigned int TFrame_Remove_Drawable_Obj(TFrame *this, TDrawable *drawable);

/**
 * @fn unsigned int TFrame_Free_Drawable(TFrame *this, const char *id)
 * @brief Method for deleting and free the first drawable found by ID.
 *
 * @param this A pointer to the frame object.
 * @param id The ID of the drawable to delete and free.
 * @return Return 1 if an drawable has been free, 0 otherwise.
 *
 * You do not have to call this method directly. You must use the
 * Free_Drawable method of the TFrame structure like this:
 * my_frame->Free_Drawable(my_frame, "MY_DRAWABLE");
 */
unsigned int TFrame_Free_Drawable(TFrame *this, const char *id);

/**
 * @fn unsigned int TFrame_Free_Drawable_Obj(TFrame *this, TDrawable *drawable)
 * @brief Method for deleting and free a drawable.
 *
 * @param this A pointer to the frame object.
 * @param drawable A pointer to the drawable object to delete and free.
 * @return Return 1 if the drawable has been free, 0 otherwise.
 *
 * You do not have to call this method directly. You must use the
 * Free_Drawable_Obj method of the TFrame structure like this:
 * my_frame->Free_Drawable_Obj(my_frame, my_drawable);
 */
unsigned int TFrame_Free_Drawable_Obj(TFrame *this, TDrawable *drawable);

/**
 * @fn unsigned int TFrame_Free_Drawables(TFrame *this, const char *id)
 * @brief Method for deleting and free all the drawables that share the same ID.
 *
 * @param this A pointer to the frame object.
 * @param id The ID of the drawables to delete and free.
 * @return Return the number of drawable deleted.
 *
 * You do not have to call this method directly. You must use the
 * Free_Drawables method of the TFrame structure like this:
 * my_frame->Free_Drawables(my_frame, "MY_DRAWABLES");
 */
unsigned int TFrame_Free_Drawables(TFrame *this, const char *id);

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
 * @fn void TFrame_Free_All_Drawables(TFrame *this, unsigned int free_strategy)
 * @brief Method for freeing all the drawable according to the free strategy given.
 *
 * @param this A pointer to the frame object.
 * @param free_strategy The strategy to be used to free the drawables.
 *
 * You do not have to call this method directly. You must use the
 * Free_All_Drawables method of the TFrame structure like this:
 * my_frame->Free_All_Drawables(my_frame, GLIB_FREE_ON_FINISH);
 */
void TFrame_Free_All_Drawables(TFrame *this, unsigned int free_strategy);

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

/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Header file for the button component of GLib.
*/

/**
 * \file button.h
 * \brief Header file for the button component of GLib.
 * \author Yohann.M, Gauthier.D, Aziz.H, William.W
 * \version 1.0
 * \date 28 janvier 2019
 *
 * The button component allows you to create a graphical button that can
 * be manipulated by GLib.
 *
 */

#ifndef GLIB_BUTTON_H_
#define GLIB_BUTTON_H_

#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "sprite.h"

/**
 * \enum EButton_State
 * \brief Constants of the states of a button.
 *
 * EButton_State is a series of predefined constants for the different
 * states of a button.
 */
typedef enum EButton_State {
    BUTTON_NORMAL,
    BUTTON_HOVER
} EButton_State ;

/**
 * \struct TButton
 * \brief Object oriented structure representing a button.
 *
 * TButton is an object that allows you to create and display a button.
 */
typedef struct TButton {

    void(*Draw)(struct TButton*, TWindow*); /*!< Draw method. */

    void(*On_Click)(struct TButton*, TWindow*); /*!< Callback called when a click event occurs. */

    void(*Event_Handler)(struct TButton*, TWindow *, SDL_Event); /*!< Method call for processing SDL event */

    void(*Free)(struct TButton*); /*!< Free (ressources) method. */

    TSprite *btn_sprite; /*!< A sprite for the button in normal state. */
    TSprite *btn_hover_sprite; /*!< A sprite for the button in hover state. */
    EButton_State state; /*!< The actual state of the button. */
    SDL_Rect pos; /*!< The position and size of the button. */

} TButton ;

/**
 * \fn TButton* New_TButton(const char *btn_s, const char *btn_hs, SDL_Rect pos, TWindow *win)
 * \brief The constructor for create a TButton object.
 *
 * \param btn_s The path of an image file for the button in normal state.
 * \param btn_hs The path of an image file for the button in hover state.
 * \param pos The position and size of the button.
 * \param win A pointer to the window object.
 * \return A memory allocated object of the button.
 */
TButton* New_TButton(const char *btn_s, const char *btn_hs, SDL_Rect pos, TWindow *win);

/**
 * \fn void TButton_Draw(TButton *this, TWindow *window)
 * \brief Method for drawing the button in the interface.
 *
 * \param this A pointer to the button object to draw.
 * \param window A pointer to the window object.
 *
 * You do not have to call this method directly. You must use the
 * Draw method of the TButton structure like this:
 * my_button->Draw(my_button, window);
 */
void TButton_Draw(TButton *this, TWindow *window);

/**
 * \fn void TButton_Event_Handler(TButton *this, TWindow *win, SDL_Event event)
 * \brief Method to process an SDL event and change the status of the button or manage clicks.
 *
 * \param this A pointer to the button object.
 * \param win A pointer to the window object.
 * \param event A SDL event.
 *
 * You do not have to call this method directly. You must use the
 * Event_Handler method of the TButton structure like this:
 * my_button->Event_Handler(my_button, window, event);
 */
void TButton_Event_Handler(TButton *this, TWindow *win, SDL_Event event);

/**
 * \fn void TButton_New_Free(TButton *this)
 * \brief Method to free all ressources take by the button.
 *
 * \param this A pointer to the button object to free.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TButton structure like this:
 * my_button->Free(my_button);
 */
void TButton_New_Free(TButton *this);

#endif

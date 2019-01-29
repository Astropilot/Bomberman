/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Header file of the inputbox component of GLib.
*/

/**
 * \file inputbox.h
 * \brief Header file of the inputbox component of GLib.
 * \author Yohann.M, Gauthier.D, Aziz.H, William.W
 * \version 1.0
 * \date 28 janvier 2019
 *
 * The input box component allows you to create a graphical input box that can
 * be manipulated by GLib.
 *
 */

#ifndef GLIB_INPUTBOX_H_
#define GLIB_INPUTBOX_H_

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "sprite.h"
#include "window.h"
#include "utils.h"

/**
 * \def MAX_STR_LEN
 *
 * The maximum length of the string for the input
 */
#define MAX_STR_LEN 15

/**
 * \struct TInput
 * \brief Object oriented structure representing a input box.
 *
 * TInput is an object that allows you to create and display a input box.
 */
typedef struct TInput {

    void(*Draw)(struct TInput*, TWindow*);                          /*!< Draw method. */

    void(*Event_Handler)(struct TInput*, TWindow *, SDL_Event);     /*!< Method call for processing SDL event */

    void(*Free)(struct TInput*);                                    /*!< Free (ressources) method. */

    char text[MAX_STR_LEN];                                         /*!< The text entered in the input box. */
    TSprite *input_sprite;                                          /*!< A sprite for the input. */
    TTF_Font *font;                                                 /*!< The font to be used for the text. */
    SDL_Color color;                                                /*!< The text color. */
    SDL_Rect pos_input;                                             /*!< The position and size of the input box. */
    SDL_Rect pos_text;                                              /*!< The position of the text in the input box. */
    unsigned int is_focus;                                          /*!< Boolean to know if the input have the focus */
    unsigned int last_time;                                         /*!< Internal variable for cursor animation timing */

} TInput ;

/**
 * \fn TInput* New_TInput(const char *sprite_file, SDL_Rect pos, TWindow *window, SDL_Color color)
 * \brief The constructor for create a TInput object.
 *
 * \param sprite_file The path of an image file for the input.
 * \param pos The position and size of the input box.
 * \param window A pointer to the window object.
 * \param color The color of the text.
 * \return A memory allocated object of the input box.
 */
TInput* New_TInput(const char *sprite_file, SDL_Rect pos, TWindow *window, SDL_Color color);

/**
 * \fn void TInput_Draw(TInput *this, TWindow *window)
 * \brief Method for drawing the input box in the interface.
 *
 * \param this A pointer to the input object to draw.
 * \param window A pointer to the window object.
 *
 * You do not have to call this method directly. You must use the
 * Draw method of the TInput structure like this:
 * my_input->Draw(my_input, window);
 */
void TInput_Draw(TInput *this, TWindow *window);

/**
 * \fn void TInput_Event_Handler(TInput *this, TWindow *win, SDL_Event event)
 * \brief Method to process an SDL event for manage text input and click focus.
 *
 * \param this A pointer to the input box object.
 * \param win A pointer to the window object.
 * \param event A SDL event.
 *
 * You do not have to call this method directly. You must use the
 * Event_Handler method of the TInput structure like this:
 * my_input->Event_Handler(my_input, window, event);
 */
void TInput_Event_Handler(TInput *this, TWindow *win, SDL_Event event);

/**
 * \fn void TInput_New_Free(TInput *this)
 * \brief Method to free all ressources take by the input box.
 *
 * \param this A pointer to the input box object to free.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TInput structure like this:
 * my_input->Free(my_input);
 */
void TInput_New_Free(TInput *this);

#endif

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
 * @file inputbox.h
 * @brief Header file of the inputbox component of GLib.
 *
 * The input box component allows you to create a graphical input box that can
 * be manipulated by GLib.
 *
 */

#ifndef GLIB_INPUTBOX_H_
#define GLIB_INPUTBOX_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "sprite.h"
#include "utils.h"

typedef struct TFrame TFrame;

/**
 * @brief Object oriented structure representing a input box.
 *
 * TInput is an object that allows you to create and display a input box.
 */
typedef struct TInput {

    void(*Draw)(struct TInput*, TFrame*);                           /*!< Draw method. */

    void(*Free)(struct TInput*);                                    /*!< Free (ressources) method. */

    unsigned int is_visible;                                        /*!< Boolean to know if the drawable can be drawed automatically. */

    void(*Event_Handler)(struct TInput*, SDL_Event);                /*!< Method call for processing SDL event */

    char *text;                                                     /*!< The text entered in the input box. */
    char *placeholder;                                              /*!< The placeholder text in the input box. */
    size_t max_len;                                                 /*!< The maximum length of the input text. */
    TSprite *input_sprite;                                          /*!< A sprite for the input. */
    TTF_Font *font;                                                 /*!< The font to be used for the text. */
    SDL_Color color;                                                /*!< The text color. */
    SDL_Rect pos_input;                                             /*!< The position and size of the input box. */
    SDL_Rect pos_text;                                              /*!< The position of the text in the input box. */
    unsigned int is_focus;                                          /*!< Boolean to know if the input have the focus */
    unsigned int last_time;                                         /*!< Internal variable for cursor animation timing */

} TInput ;

/**
 * @fn TInput* TInput* New_TInput(TFrame *frame, const char *sprite_file, SDL_Rect pos, SDL_Color color, size_t len, const char *placeholder)
 * @brief The constructor for create a TInput object.
 *
 * @param frame A pointer to the frame object.
 * @param sprite_file The path of an image file for the input.
 * @param pos The position and size of the input box.
 * @param color The color of the text.
 * @param len The maximum length of the input text.
 * @param placeholder A placeholder text when no text has been entered.
 * @return A memory allocated object of the input box.
 */
TInput* New_TInput(TFrame *frame, const char *sprite_file, SDL_Rect pos, SDL_Color color, size_t len, const char *placeholder);

/**
 * @fn void TInput_Draw(TInput *this, TFrame *frame)
 * @brief Method for drawing the input box in the interface.
 *
 * @param this A pointer to the input object to draw.
 * @param frame A pointer to the frame object.
 *
 * You do not have to call this method directly. You must use the
 * Draw method of the TInput structure like this:
 * my_input->Draw(my_input, frame);
 */
void TInput_Draw(TInput *this, TFrame *frame);

/**
 * @fn void TInput_Event_Handler(TInput *this, SDL_Event event)
 * @brief Method to process an SDL event for manage text input and click focus.
 *
 * @param this A pointer to the input box object.
 * @param event A SDL event.
 *
 * You do not have to call this method directly. You must use the
 * Event_Handler method of the TInput structure like this:
 * my_input->Event_Handler(my_input, event);
 */
void TInput_Event_Handler(TInput *this, SDL_Event event);

/**
 * @fn void TInput_New_Free(TInput *this)
 * @brief Method to free all ressources take by the input box.
 *
 * @param this A pointer to the input box object to free.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TInput structure like this:
 * my_input->Free(my_input);
 */
void TInput_New_Free(TInput *this);

#endif

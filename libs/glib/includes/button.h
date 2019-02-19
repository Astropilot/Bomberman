/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Header file of the button component of GLib.
*/

/**
 * @file button.h
 * @brief Header file of the button component of GLib.
 * @author Yohann.M, Gauthier.D, Aziz.H, William.W
 * @version 1.0
 * @date 28 janvier 2019
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

typedef struct TFrame TFrame;

/**
 * @enum EButton_State
 * @brief Constants of the states of a button.
 *
 * EButton_State is a series of predefined constants for the different
 * states of a button.
 */
typedef enum {
    BUTTON_NORMAL,  /*!< The normal state of the button. */
    BUTTON_HOVER    /*!< The hover state of the button. */
} EButton_State ;

/**
 * @struct TButton
 * @brief Object oriented structure representing a button.
 *
 * TButton is an object that allows you to create and display a button.
 */
typedef struct {

    void(*Draw)(struct TButton*, TFrame*); /*!< Draw method. */

    void(*Free)(struct TButton*); /*!< Free (ressources) method. */

    void(*On_Click)(struct TButton*, TFrame*); /*!< Callback called when a click event occurs. */

    void(*Event_Handler)(struct TButton*, TFrame *, SDL_Event); /*!< Method call for processing SDL event */

    TSprite *btn_sprite; /*!< A sprite for the button in normal state. */
    TSprite *btn_hover_sprite; /*!< A sprite for the button in hover state. */
    EButton_State state; /*!< The actual state of the button. */
    SDL_Rect pos; /*!< The position and size of the button. */

} TButton ;

/**
 * @fn TButton* New_TButton(TFrame *frame, const char *btn_s, const char *btn_hs, SDL_Rect pos)
 * @brief The constructor for create a TButton object.
 *
 * @param frame A pointer to the frame object.
 * @param btn_s The path of an image file for the button in normal state.
 * @param btn_hs The path of an image file for the button in hover state.
 * @param pos The position and size of the button.
 * @return A memory allocated object of the button.
 */
TButton* New_TButton(TFrame *frame, const char *btn_s, const char *btn_hs, SDL_Rect pos);

/**
 * @fn void TButton_Draw(TButton *this, TFrame *frame)
 * @brief Method for drawing the button in the interface.
 *
 * @param this A pointer to the button object to draw.
 * @param frame A pointer to the frame object.
 *
 * You do not have to call this method directly. You must use the
 * Draw method of the TButton structure like this:
 * my_button->Draw(my_button, frame);
 */
void TButton_Draw(TButton *this, TFrame *frame);

/**
 * @fn void TButton_Event_Handler(TButton *this, TFrame *frame, SDL_Event event)
 * @brief Method to process an SDL event and change the status of the button or manage clicks.
 *
 * @param this A pointer to the button object.
 * @param frame A pointer to the frame object.
 * @param event A SDL event.
 *
 * You do not have to call this method directly. You must use the
 * Event_Handler method of the TButton structure like this:
 * my_button->Event_Handler(my_button, frame, event);
 */
void TButton_Event_Handler(TButton *this, TFrame *frame, SDL_Event event);

/**
 * @fn void TButton_New_Free(TButton *this)
 * @brief Method to free all ressources take by the button.
 *
 * @param this A pointer to the button object to free.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TButton structure like this:
 * my_button->Free(my_button);
 */
void TButton_New_Free(TButton *this);

#endif

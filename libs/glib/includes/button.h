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
 * @file button.h
 * @brief Header file of the button component of GLib.
 *
 * The button component allows you to create a graphical button that can
 * be manipulated by GLib.
 *
 */

#ifndef GLIB_BUTTON_H_
#define GLIB_BUTTON_H_

#include <SDL2/SDL.h>

#include "scene.h"
#include "sprite.h"

typedef struct TScene TScene;

/**
 * @brief Constants of the states of a button.
 *
 * TButton_State is a series of predefined constants for the different
 * states of a button.
 */
typedef enum TButton_State {
    BUTTON_NORMAL,  /*!< The normal state of the button. */
    BUTTON_HOVER    /*!< The hover state of the button. */
} TButton_State ;

/**
 * @brief Object oriented structure representing a button.
 *
 * TButton is an object that allows you to create and display a button.
 */
typedef struct TButton {

    void(*Draw)(struct TButton*, TScene*);                      /*!< Draw method. */

    void(*Free)(struct TButton*);                               /*!< Free (ressources) method. */

    unsigned int is_visible;                                    /*!< Boolean to know if the drawable can be drawed automatically. */

    void(*On_Click)(struct TButton*, TScene*);                  /*!< Callback called when a click event occurs. */

    void(*Event_Handler)(struct TButton*, TScene*, SDL_Event);  /*!< Method call for processing SDL event */

    TSprite *btn_sprite;            /*!< A sprite for the button in normal state. */
    TSprite *btn_hover_sprite;      /*!< A sprite for the button in hover state. */
    TButton_State state;            /*!< The actual state of the button. */
    SDL_Rect pos;                   /*!< The position and size of the button. */

} TButton ;

/**
 * @brief The constructor for create a TButton object.
 *
 * @param scene A pointer to the scene object.
 * @param btn_s The path of an image file for the button in normal state.
 * @param btn_hs The path of an image file for the button in hover state.
 * @param pos The position and size of the button.
 * @return A memory allocated object of the button.
 */
TButton* New_TButton(TScene *scene, const char *btn_s, const char *btn_hs, SDL_Rect pos);

/**
 * @brief Method for drawing the button in the interface.
 *
 * @param this A pointer to the button object to draw.
 * @param scene A pointer to the scene object.
 *
 * You do not have to call this method directly. You must use the
 * Draw method of the TButton structure like this:
 * my_button->Draw(my_button, scene);
 */
void TButton_Draw(TButton *this, TScene *scene);

/**
 * @brief Method to process an SDL event and change the status of the button or manage clicks.
 *
 * @param this A pointer to the button object.
 * @param scene A pointer to the scene object.
 * @param event A SDL event.
 *
 * You do not have to call this method directly. You must use the
 * Event_Handler method of the TButton structure like this:
 * my_button->Event_Handler(my_button, scene, event);
 */
void TButton_Event_Handler(TButton *this, TScene *scene, SDL_Event event);

/**
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

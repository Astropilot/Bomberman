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
 * @file slider.h
 * @brief Header file of the slider component of GLib.
 *
 * The slider component allows you to create a graphical slider that can
 * be manipulated by GLib.
 *
 */

#ifndef GLIB_SLIDER_H_
#define GLIB_SLIDER_H_

#include <SDL2/SDL.h>

#include "scene.h"
#include "sprite.h"

typedef struct TScene TScene;

/**
 * @brief Object oriented structure representing a slider.
 *
 * TSlider is an object that allows you to create and display a slider.
 */
typedef struct TSlider {

    void(*Draw)(struct TSlider*, TScene*);                      /*!< Draw method. */

    void(*Free)(struct TSlider*);                               /*!< Free (ressources) method. */

    unsigned int is_visible;                                    /*!< Boolean to know if the drawable can be drawed automatically. */

    void(*On_ValueChange)(struct TSlider*, TScene*, int);       /*!< Callback called when a the slider value change. */

    void(*Event_Handler)(struct TSlider*, TScene*, SDL_Event);  /*!< Method call for processing SDL event */

    TSprite *sprite_bg;             /*!< A sprite for the slider bar background. */
    TSprite *sprite_btn;            /*!< A sprite for the slider button. */
    int value;                      /*!< The value of the slider. */
    int min_value;                  /*!< The minimum value that the slider can take. */
    int max_value;                  /*!< The maximum value that the slider can take. */
    SDL_Rect pos;                   /*!< The position and size of the slider. */
    SDL_Point btn_size;             /*!< The size of the slider's button. */
    unsigned int lclick_pressed;    /*!< Boolean to know if the left mouse button is pressed. */
} TSlider ;

/**
 * @brief The constructor for create a TSlider object.
 *
 * @param scene A pointer to the scene object.
 * @param bg_s The path of an image file for the slider's background.
 * @param btn_s The path of an image file for the slider's button.
 * @param pos The position and size of the slider.
 * @param btn_size The size of the slider's button.
 * @param min_val The minimum value that the slider can take.
 * @param max_val The maximum value that the slider can take.
 * @param value The default value of the slider.
 * @return A memory allocated object of the slider.
 */
TSlider* New_TSlider(
    TScene *scene, const char *bg_s, const char *btn_s,
    SDL_Rect pos, SDL_Point btn_size, int min_val, int max_val, int value
);

/**
 * @brief Method for drawing the slider in the interface.
 *
 * @param this A pointer to the slider object to draw.
 * @param scene A pointer to the scene object.
 *
 * You do not have to call this method directly. You must use the
 * Draw method of the TSlider structure like this:
 * my_slider->Draw(my_slider, scene);
 */
void TSlider_Draw(TSlider *this, TScene *scene);

/**
 * @brief Method to process an SDL event and change the value of the slider.
 *
 * @param this A pointer to the slider object.
 * @param scene A pointer to the scene object.
 * @param event A SDL event.
 *
 * You do not have to call this method directly. You must use the
 * Event_Handler method of the TSlider structure like this:
 * my_slider->Event_Handler(my_slider, scene, event);
 */
void TSlider_Event_Handler(TSlider *this, TScene *scene, SDL_Event event);

/**
 * @brief Method to free all ressources take by the slider.
 *
 * @param this A pointer to the slider object to free.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TSlider structure like this:
 * my_slider->Free(my_slider);
 */
void TSlider_New_Free(TSlider *this);

#endif

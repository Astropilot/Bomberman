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
 * @file text.h
 * @brief Header file of the text component of GLib.
 *
 * The text component allows you to create a graphical text that can
 * be manipulated by GLib.
 *
 */

#ifndef GLIB_TEXT_H_
#define GLIB_TEXT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct TScene TScene;

/**
 * @brief Object oriented structure representing a text.
 *
 * TText is an object that allows you to create and display a text.
 */
typedef struct TText {

    void(*Draw)(struct TText*, TScene*);                        /*!< Draw method. */

    void(*Free)(struct TText*);                                 /*!< Free (ressources) method. */

    unsigned int is_visible;                                    /*!< Boolean to know if the drawable can be drawed automatically. */

    void(*Change_Text)(struct TText*, TScene*, const char*);    /*!< Method to change the actual text. */

    char *text;                                 /*!< The text to be drawed. */
    SDL_Texture *texture;                       /*!< The SDL texture of the text. */
    SDL_Rect pos;                               /*!< The position of the text. */
    SDL_Color color;                            /*!< The color of the text. */
    TTF_Font *font;                             /*!< The font of the text. */

} TText ;

/**
 * @brief The constructor for create a TText object.
 *
 * @param scene A pointer to the window object.
 * @param text The text to draw.
 * @param font The font of the text.
 * @param color The color of the text.
 * @param pos The position of the text.
 * @return A memory allocated object of the text.
 */
TText* New_TText(TScene *scene, const char *text, TTF_Font *font, SDL_Color color, SDL_Rect pos);

/**
 * @brief Method for drawing the text in the interface.
 *
 * @param this A pointer to the text object to draw.
 * @param scene A pointer to the scene object.
 *
 * You do not have to call this method directly. You must use the
 * Draw method of the TText structure like this:
 * my_text->Draw(my_text, scene);
 */
void TText_Draw(TText *this, TScene *scene);

/**
 * @brief Method for changing the text.
 *
 * @param this A pointer to the text object.
 * @param scene A pointer to the scene object.
 * @param text The text to change.
 *
 * You do not have to call this method directly. You must use the
 * Change_Text method of the TText structure like this:
 * my_text->Change_Text(my_text, scene, "My text");
 */
void TText_Change_Text(TText *this, TScene *scene, const char *text);

/**
 * @brief Method to free all ressources take by the text.
 *
 * @param this A pointer to the text object to free.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TText structure like this:
 * my_text->Free(my_text);
 */
void TText_New_Free(TText *this);

#endif

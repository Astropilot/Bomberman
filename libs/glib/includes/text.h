/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Header file of the text component of GLib.
*/

/**
 * @file text.h
 * @brief Header file of the text component of GLib.
 * @author Yohann.M, Gauthier.D, Aziz.H, William.W
 * @version 1.0
 * @date 28 janvier 2019
 *
 * The text component allows you to create a graphical text that can
 * be manipulated by GLib.
 *
 */

#ifndef GLIB_TEXT_H_
#define GLIB_TEXT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct TFrame TFrame;

/**
 * @brief Object oriented structure representing a text.
 *
 * TText is an object that allows you to create and display a text.
 */
typedef struct TText {

    void(*Draw)(struct TText*, TFrame*);        /*!< Draw method. */

    void(*Free)(struct TText*);                 /*!< Free (ressources) method. */

    unsigned int is_visible;                    /*!< Boolean to know if the drawable can be drawed automatically. */

    void(*Change_Text)(struct TText*, TFrame*, const char*); /*!< Method to change the actual text. */

    char *text;                                 /*!< The text to be drawed. */
    SDL_Texture *texture;                       /*!< The SDL texture of the text. */
    SDL_Rect pos;                               /*!< The position of the text. */
    SDL_Color color;                            /*!< The color of the text. */
    TTF_Font *font;                             /*!< The font of the text. */

} TText ;

/**
 * @fn TText* New_TText(TFrame *frame, const char *text, TTF_Font *font, SDL_Color color, SDL_Rect pos)
 * @brief The constructor for create a TText object.
 *
 * @param frame A pointer to the window object.
 * @param text The text to draw.
 * @param font The font of the text.
 * @param color The color of the text.
 * @param pos The position of the text.
 * @return A memory allocated object of the text.
 */
TText* New_TText(TFrame *frame, const char *text, TTF_Font *font, SDL_Color color, SDL_Rect pos);

/**
 * @fn void TText_Draw(TText *this, TFrame *frame)
 * @brief Method for drawing the text in the interface.
 *
 * @param this A pointer to the text object to draw.
 * @param frame A pointer to the frame object.
 *
 * You do not have to call this method directly. You must use the
 * Draw method of the TText structure like this:
 * my_text->Draw(my_text, frame);
 */
void TText_Draw(TText *this, TFrame *frame);

/**
 * @fn void Change_Text(TText *this, TFrame *frame, const char *text)
 * @brief Method for changing the text.
 *
 * @param this A pointer to the text object.
 * @param frame A pointer to the frame object.
 * @param text The text to change.
 *
 * You do not have to call this method directly. You must use the
 * Change_Text method of the TText structure like this:
 * my_text->Change_Text(my_text, frame, "My text");
 */
void TText_Change_Text(TText *this, TFrame *frame, const char *text);

/**
 * @fn void TText_New_Free(TText *this)
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

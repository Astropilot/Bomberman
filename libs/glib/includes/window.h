/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Header file for the TWindow of GLib.
*/

/**
 * \file window.h
 * \brief Header file for the TWindow of GLib.
 * \author Yohann.M, Gauthier.D, Aziz.H, William.W
 * \version 1.0
 * \date 28 janvier 2019
 *
 * The TWindow allows you to create a SDL window that can
 * be manipulated by GLib and handle TFrames and game loop.
 *
 */

#ifndef GLIB_WINDOW_H_
#define GLIB_WINDOW_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "frame.h"

/**
 * \struct TWindow
 * \brief Object oriented structure representing a window.
 *
 * TWindow is an object that allows you to create and display a window.
 */
typedef struct TWindow {

    int(*Create_Window)(struct TWindow*, const char*, int, int, const char*);   /*!< Method for creating the SDL window. */
    void(*Add_Frame)(struct TWindow*, TFrame*);                                 /*!< Method for adding a TFrame to the window. */
    void(*Show_Frame)(struct TWindow*, const char *, int argc, ...);            /*!< Method for showing a frame by its ID with optionnals parameters. */
    void(*Free)(struct TWindow*);                                               /*!< Method for free all ressources. */

    SDL_Window *screen_window;                                                  /*!< The SDL_Window pointer. */
    SDL_Renderer *renderer_window;                                              /*!< The SDL_Renderer pointer. */
    unsigned int finished;                                                      /*!< Boolean to know if the window need to be closed. */
    TFrame_Node *frames_head;                                                   /*!< A linked list of frames (TFrame). */
    TFrame *shown_frame;                                                        /*!< The actual frame to be show. */

} TWindow ;

/**
 * \fn TWindow* New_TWindow(void)
 * \brief The constructor for create a TWindow object.
 *
 * \return A memory allocated object of the window.
 */
TWindow* New_TWindow(void);

/**
 * \fn int TWindow_Create_Window(TWindow *this, const char *title, int width, int height, const char *frame_id)
 * \brief Method for creating and showing the SDL window.
 *
 * \param this A pointer to the window object.
 * \param title The title of the SDL window.
 * \param width The width of the SDL window.
 * \param height The height of the SDL window.
 * \param frame_id The ID of the frame to be show first.
 *
 * You do not have to call this method directly. You must use the
 * Create_Window method of the TWindow structure like this:
 * my_window->Create_Window(my_window, "My window", 50, 50, "MY_FRAME");
 */
int TWindow_Create_Window(TWindow *this, const char *title, int width, int height, const char *frame_id);

/**
 * \fn void TWindow_Add_Frame(TWindow *this, TFrame *frame)
 * \brief Method for adding a frame to the window.
 *
 * \param this A pointer to the window object.
 * \param frame The frame to add.
 *
 * You do not have to call this method directly. You must use the
 * Add_Frame method of the TWindow structure like this:
 * my_window->Add_Frame(my_window, my_frame);
 */
void TWindow_Add_Frame(TWindow *this, TFrame *frame);

/**
 * \fn void TWindow_Show_Frame(TWindow *this, const char *frame_id, int argc, ...)
 * \brief Method for showing a frame to the window.
 *
 * \param this A pointer to the window object.
 * \param frame The frame ID to show.
 * \param argc The number of optionnals parameters for the frame to show. To be followed by the parameters if argc > 0.
 *
 * You do not have to call this method directly. You must use the
 * Show_Frame method of the TWindow structure like this:
 * my_window->Show_Frame(my_window, "MY_FRAME", 0);
 */
void TWindow_Show_Frame(TWindow *this, const char *frame_id, int argc, ...);

/**
 * \fn void TWindow_New_Free(TWindow *this)
 * \brief Method to free all ressources take by the window and frames.
 *
 * \param this A pointer to the window object to free.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TWindow structure like this:
 * my_window->Free(my_window);
 */
void TWindow_New_Free(TWindow *this);

#endif

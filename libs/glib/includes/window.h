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
 * @file window.h
 * @brief Header file of the TWindow of GLib.
 *
 * The TWindow allows you to create a SDL window that can
 * be manipulated by GLib and handle TScenes and game loop.
 *
 */

#ifndef GLIB_WINDOW_H_
#define GLIB_WINDOW_H_

#include <stdarg.h>
#include <SDL2/SDL.h>

#include "scene.h"
#include "cache.h"

/**
 * @brief Object oriented structure representing a window.
 *
 * TWindow is an object that allows you to create and display a window.
 */
typedef struct TWindow {

    int(*Create_Window)(struct TWindow*, const char*, int, int, const char*, unsigned int);     /*!< Method for creating the SDL window. */
    void(*Add_Scene)(struct TWindow*, TScene*);                                                 /*!< Method for adding a TScene to the window. */
    void(*Show_Scene)(struct TWindow*, const char *, int argc, ...);                            /*!< Method for showing a scene by its ID with optionnals parameters. */
    void(*Free)(struct TWindow*);                                                               /*!< Method for free all ressources. */

    SDL_Window *screen_window;                                                  /*!< The SDL_Window pointer. */
    SDL_Renderer *renderer_window;                                              /*!< The SDL_Renderer pointer. */
    unsigned int finished;                                                      /*!< Boolean to know if the window need to be closed. */
    TScene_Node *scenes_head;                                                   /*!< A linked list of scenes (TScene). */
    TScene *shown_scene;                                                        /*!< The actual scene to be show. */
    unsigned int fps;                                                           /*!< The delay in milliseconds between each game loop. */
    TResourceCache *cache_manager;                                              /*!< The cache manager for resources. */

} TWindow ;

/**
 * @fn TWindow* New_TWindow(unsigned int max_caching)
 * @brief The constructor for create a TWindow object.
 *
 * @param max_caching The maximum amount of resources that can be cached.
 * @return A memory allocated object of the window.
 */
TWindow* New_TWindow(unsigned int max_caching);

/**
 * @fn int TWindow_Create_Window(TWindow *this, const char *title, int width, int height, const char *scene_id, unsigned int fps)
 * @brief Method for creating and showing the SDL window.
 *
 * @param this A pointer to the window object.
 * @param title The title of the SDL window.
 * @param width The width of the SDL window.
 * @param height The height of the SDL window.
 * @param scene_id The ID of the scene to be show first.
 * @param fps The delay in milliseconds between each game loop.
 *
 * You do not have to call this method directly. You must use the
 * Create_Window method of the TWindow structure like this:
 * my_window->Create_Window(my_window, "My window", 50, 50, "MY_SCENE", 30);
 */
int TWindow_Create_Window(TWindow *this, const char *title, int width, int height, const char *scene_id, unsigned int fps);

/**
 * @fn void TWindow_Add_Scene(TWindow *this, TScene *scene)
 * @brief Method for adding a scene to the window.
 *
 * @param this A pointer to the window object.
 * @param scene The scene to add.
 *
 * You do not have to call this method directly. You must use the
 * Add_Scene method of the TWindow structure like this:
 * my_window->Add_Scene(my_window, my_scene);
 */
void TWindow_Add_Scene(TWindow *this, TScene *scene);

/**
 * @fn void TWindow_Show_Scene(TWindow *this, const char *scene_id, int argc, ...)
 * @brief Method for showing a scene to the window.
 *
 * @param this A pointer to the window object.
 * @param scene_id The scene ID to show.
 * @param argc The number of optionnals parameters for the scene to show. To be followed by the parameters if argc > 0.
 *
 * You do not have to call this method directly. You must use the
 * Show_Scene method of the TWindow structure like this:
 * my_window->Show_Scene(my_window, "MY_SCENE", 0);
 */
void TWindow_Show_Scene(TWindow *this, const char *scene_id, int argc, ...);

/**
 * @fn void TWindow_New_Free(TWindow *this)
 * @brief Method to free all ressources take by the window and scenes.
 *
 * @param this A pointer to the window object to free.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TWindow structure like this:
 * my_window->Free(my_window);
 */
void TWindow_New_Free(TWindow *this);

#endif

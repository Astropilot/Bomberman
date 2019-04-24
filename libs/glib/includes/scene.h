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
 * @file scene.h
 * @brief Header file of the TScene of GLib.
 *
 * The TScene object allow you to create an isolated graphic environnement
 * whith it own logic.
 *
 */

#ifndef GLIB_SCENE_H_
#define GLIB_SCENE_H_

#include <stdarg.h>

#include "drawable.h"

#define GLIB_NO_FREE 0          /*!< Flag for not free a resource at any moment. */
#define GLIB_FREE_ON_FINISH 1   /*!< Flag for free a resource when scene finished. */
#define GLIB_FREE_ON_UNLOAD 2   /*!< Flag for free a resource when scene unloaded. */

typedef struct TWindow TWindow;

/**
 * @brief Object oriented structure representing a scene.
 *
 * TScene is an object that allows you to create and define a new scene.
 */
typedef struct TScene {

    void(*Add_Drawable)(struct TScene*, TDrawable*, const char*, unsigned int, unsigned int);/*!< Method for adding a drawable with an ID and a priority. */

    TDrawable*(*Remove_Drawable)(struct TScene*, const char*);                              /*!< Method for deleting a drawable by its ID. */

    unsigned int(*Remove_Drawable_Obj)(struct TScene*, TDrawable*);                         /*!< Method for deleting a drawable. */

    unsigned int(*Free_Drawable)(struct TScene*, const char*);                              /*!< Method for deleting and freeing the first drawable found by its ID. */

    unsigned int(*Free_Drawable_Obj)(struct TScene*, TDrawable*);                           /*!< Method for deleting and freeing a drawable. */

    unsigned int(*Free_Drawables)(struct TScene*, const char*);                             /*!< Method for deleting and freeing all drawables that share the same ID. */

    TDrawable*(*Get_Drawable)(struct TScene*, const char*);                                 /*!< Method for getting a drawable by its ID. */

    void(*Draw_Drawables)(struct TScene*);                                                  /*!< Method for drawing all the drawables added. */

    void(*Free_All_Drawables)(struct TScene*, unsigned int);                                /*!< Method for freeing all the drawable according to the free strategy given. */

    void(*Play_BackgroundMusic)(struct TScene*, const char*, int);                          /*!< Method for play a background music. */

    int(*Is_BackgroundMusic_Playing)(struct TScene*);                                       /*!< Method for know if the music is playing. */

    int(*Is_BackgroundMusic_Paused)(struct TScene*);                                        /*!< Method for know if the music is paused. */

    void(*Pause_BackgroundMusic)(struct TScene*, int);                                      /*!< Method for pause playing the background music. */

    void(*Resume_BackgroundMusic)(struct TScene*);                                          /*!< Method for unpause the background music. */

    void(*On_Init)(struct TScene*);                                                         /*!< Method to be defined on the TScene creation. Called one time on first show. */

    void(*On_Load)(struct TScene*, int, va_list);                                           /*!< Method to be defined on the TScene creation. Called each time the scene is shown. */

    void(*On_Event)(struct TScene*, SDL_Event);                                             /*!< Method to be defined on the TScene creation. Called on each SDL event. */

    void(*On_Tick)(struct TScene*);                                                         /*!< Method to be defined on the TScene creation. Called on each tick in game loop */

    void(*On_Unload)(struct TScene*);                                                       /*!< Method to be defined on the TScene creation. Called each time the scene become invisible. */

    void(*On_Finish)(struct TScene*);                                                       /*!< Method to be defined on the TScene creation. Called one time at the end of the program. */

    void(*Free)(struct TScene*);                                                            /*!< Method for free all TScene ressources, include drawables. */

    TWindow *window;                                        /*!< The main window. */
    char *scene_id;                                         /*!< The ID of the scene. */
    unsigned int initialized;                               /*!< Boolean to know if the scene has been initialized or not. */
    TDrawable_Node *drawables_head;                         /*!< A linked list of drawables. */

} TScene ;

/**
 * @brief A linked list node for scenes.
 *
 * TScene_Node is an linked list node for stock TScene objects.
 */
typedef struct TScene_Node {
    TScene *scene;                  /*!< The scene object. */
    struct TScene_Node *next;       /*!< A pointer to the next TScene_Node. */
} TScene_Node ;

/**
 * @brief The constructor for create a TScene object.
 *
 * @param scene_id A unique ID.
 * @return A memory allocated object of the scene.
 */
TScene* New_TScene(const char *scene_id);

/**
 * @brief Method for adding a drawable to the scene.
 *
 * @param this A pointer to the scene object.
 * @param drawable A generic drawable.
 * @param id An unique ID for the drawable.
 * @param priority The drawing priority. The lower the priority (close to 1), the more it will be drawn last.
 * @param free_strategy The free strategy to use for this resource.
 *
 * You do not have to call this method directly. You must use the
 * Add_Drawable method of the TScene structure like this:
 * my_scene->Add_Drawable(my_scene, (TDrawable*)my_drawable, "MY_DRAWABLE", 1, GLIB_FREE_ON_FINISH);
 */
void TScene_Add_Drawable(TScene *this, TDrawable *drawable, const char *id, unsigned int priority, unsigned int free_strategy);

/**
 * @brief Method for deleting a drawable. The drawable is not free !
 *
 * @param this A pointer to the scene object.
 * @param id The ID of the drawable to delete.
 * @return The drawable object deleted from the scene.
 *
 * You do not have to call this method directly. You must use the
 * Remove_Drawable method of the TScene structure like this:
 * my_scene->Remove_Drawable(my_scene, "MY_DRAWABLE");
 */
TDrawable *TScene_Remove_Drawable(TScene *this, const char *id);

/**
 * @brief Method for deleting a drawable. The drawable is not free !
 *
 * @param this A pointer to the scene object.
 * @param drawable A pointer to the drawable object to remove.
 * @return Return 1 if an drawable has been deleted, 0 otherwise.
 *
 * You do not have to call this method directly. You must use the
 * Remove_Drawable_Obj method of the TScene structure like this:
 * my_scene->Remove_Drawable_Obj(my_scene, my_drawable);
 */
unsigned int TScene_Remove_Drawable_Obj(TScene *this, TDrawable *drawable);

/**
 * @brief Method for deleting and free the first drawable found by ID.
 *
 * @param this A pointer to the scene object.
 * @param id The ID of the drawable to delete and free.
 * @return Return 1 if an drawable has been free, 0 otherwise.
 *
 * You do not have to call this method directly. You must use the
 * Free_Drawable method of the TScene structure like this:
 * my_scene->Free_Drawable(my_scene, "MY_DRAWABLE");
 */
unsigned int TScene_Free_Drawable(TScene *this, const char *id);

/**
 * @brief Method for deleting and free a drawable.
 *
 * @param this A pointer to the scene object.
 * @param drawable A pointer to the drawable object to delete and free.
 * @return Return 1 if the drawable has been free, 0 otherwise.
 *
 * You do not have to call this method directly. You must use the
 * Free_Drawable_Obj method of the TScene structure like this:
 * my_scene->Free_Drawable_Obj(my_scene, my_drawable);
 */
unsigned int TScene_Free_Drawable_Obj(TScene *this, TDrawable *drawable);

/**
 * @brief Method for deleting and free all the drawables that share the same ID.
 *
 * @param this A pointer to the scene object.
 * @param id The ID of the drawables to delete and free.
 * @return Return the number of drawable deleted.
 *
 * You do not have to call this method directly. You must use the
 * Free_Drawables method of the TScene structure like this:
 * my_scene->Free_Drawables(my_scene, "MY_DRAWABLES");
 */
unsigned int TScene_Free_Drawables(TScene *this, const char *id);

/**
 * @brief Method for getting a drawable.
 *
 * @param this A pointer to the scene object.
 * @param id The ID of the drawable to get.
 * @return The drawable object.
 *
 * You do not have to call this method directly. You must use the
 * Get_Drawable method of the TScene structure like this:
 * my_scene->Get_Drawable(my_scene, "MY_DRAWABLE");
 */
TDrawable *TScene_Get_Drawable(TScene *this, const char *id);

/**
 * @brief Method for drawing all drawables in the scene.
 *
 * @param this A pointer to the scene object.
 *
 * You do not have to call this method directly. You must use the
 * Draw_Drawables method of the TScene structure like this:
 * my_scene->Draw_Drawables(my_scene);
 */
void TScene_Draw_Drawables(TScene *this);

/**
 * @brief Method for freeing all the drawable according to the free strategy given.
 *
 * @param this A pointer to the scene object.
 * @param free_strategy The strategy to be used to free the drawables.
 *
 * You do not have to call this method directly. You must use the
 * Free_All_Drawables method of the TScene structure like this:
 * my_scene->Free_All_Drawables(my_scene, GLIB_FREE_ON_FINISH);
 */
void TScene_Free_All_Drawables(TScene *this, unsigned int free_strategy);

/**
 * @brief Method for play a background music.
 *
 * @param this A pointer to the scene object.
 * @param music_path The path to the music file.
 * @param plays The number of times the music must be played, -1 for loop playback.
 *
 * You do not have to call this method directly. You must use the
 * Play_BackgroundMusic method of the TScene structure like this:
 * my_scene->Play_BackgroundMusic(my_scene, "my_music.wav", 1);
 */
void TScene_Play_BackgroundMusic(TScene *this, const char *music_path, int plays);

/**
 * @brief Method for know if the music is playing.
 *
 * @param this A pointer to the scene object.
 * @return Return 1 if the music is playing, 0 otherwise.
 *
 * You do not have to call this method directly. You must use the
 * Is_BackgroundMusic_Playing method of the TScene structure like this:
 * my_scene->Is_BackgroundMusic_Playing(my_scene);
 */
int TScene_Is_BackgroundMusic_Playing(TScene *this);

/**
 * @brief Method for know if the music is paused.
 *
 * @param this A pointer to the scene object.
 * @return Return 1 if the music is paused, 0 otherwise.
 *
 * You do not have to call this method directly. You must use the
 * Is_BackgroundMusic_Paused method of the TScene structure like this:
 * my_scene->Is_BackgroundMusic_Paused(my_scene);
 */
int TScene_Is_BackgroundMusic_Paused(TScene *this);

/**
 * @brief Method for pause playing the background music.
 *
 * @param this A pointer to the scene object.
 * @param reset Set 1 to completly stop the music, 0 if you want to pause for futur resume.
 *
 * You do not have to call this method directly. You must use the
 * Pause_BackgroundMusic method of the TScene structure like this:
 * my_scene->Pause_BackgroundMusic(my_scene, 0); // Pause
 */
void TScene_Pause_BackgroundMusic(TScene *this, int reset);

/**
 * @brief Method for unpause the background music.
 *
 * @param this A pointer to the scene object.
 *
 * You do not have to call this method directly. You must use the
 * Resume_BackgroundMusic method of the TScene structure like this:
 * my_scene->Resume_BackgroundMusic(my_scene);
 */
void TScene_Resume_BackgroundMusic(TScene *this);

/**
 * @brief Method to free all ressources take by the scene, drawables included.
 *
 * @param this A pointer to the scene object to free.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TScene structure like this:
 * my_scene->Free(my_scene);
 */
void TScene_New_Free(TScene *this);

#endif

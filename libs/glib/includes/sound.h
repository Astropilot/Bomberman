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
 * @file sound.h
 * @brief Header file of the sound component of GLib.
 *
 * The sound component allows you to create a sound effect to play.
 *
 */

#ifndef GLIB_SOUND_H_
#define GLIB_SOUND_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "scene.h"

typedef struct TScene TScene;

/**
 * @brief Object oriented structure representing a sound effect.
 *
 * TSound is an object that allows you to create and play sound effects.
 */
typedef struct TSound {

    void(*Draw)(struct TSound*, TScene*);                       /*!< Draw method. */

    void(*Free)(struct TSound*);                                /*!< Free (ressources) method. */

    unsigned int is_visible;                                    /*!< Boolean to know if the drawable can be drawed automatically. */

    void(*Play)(struct TSound*, int);                           /*!< Method for playing a sound effect. */

    void(*Stop)(struct TSound*);                                /*!< Method for stop playing a sound effect. */

    Mix_Chunk *sound;                                           /*!< The SDL structure for getting a sound. */
    int channel;                                                /*!< The channel ID where the sound is played at. */

} TSound ;

/**
 * @brief The constructor for create a TSound object.
 *
 * @param scene A pointer to the scene object.
 * @param sound_path The path of the sound file.
 * @return A memory allocated object of the sound.
 */
TSound* New_TSound(TScene *scene, const char *sound_path);

/**
 * @brief Method for playing the sound right now.
 *
 * @param this A pointer to the sound object to play.
 * @param plays The number of times the sound must be played.
 *
 * You do not have to call this method directly. You must use the
 * Play method of the TSound structure like this:
 * my_sound->Play(my_sound, 1);
 */
void TSound_Play(TSound *this, int plays);

/**
 * @brief Method for stopping the sound.
 *
 * @param this A pointer to the sound object to stop.
 *
 * You do not have to call this method directly. You must use the
 * Stop method of the TSound structure like this:
 * my_sound->Stop(my_sound);
 */
void TSound_Stop(TSound *this);

/**
 * @brief Method to free all ressources take by the sound effect.
 *
 * @param this A pointer to the sound effect object to free.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TSound structure like this:
 * my_sound->Free(my_sound);
 */
void TSound_New_Free(TSound *this);

#endif

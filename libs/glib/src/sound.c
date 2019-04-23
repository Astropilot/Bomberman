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

#include <SDL2/SDL.h>

#include "sound.h"
#include "scene.h"
#include "window.h"
#include "resource.h"

static void TSound_Init(TSound *this, TScene *scene, const char *sound_path);

TSound* New_TSound(TScene *scene, const char *sound_path)
{
    TSound *this = malloc(sizeof(TSound));

    if(!this) return (NULL);
    TSound_Init(this, scene, sound_path);
    this->Free = TSound_New_Free;
    return (this);
}

static void TSound_Init(TSound *this, TScene *scene, const char *sound_path)
{
    if (!this || !scene || !sound_path) return;

    TResourceCache *cache = scene->window->cache_manager;

    this->Draw = NULL;
    this->Play = TSound_Play;
    this->Stop = TSound_Stop;
    this->sound = (Mix_Chunk*)cache->FetchResource(cache, sound_path, SHORT_AUDIO);
    this->channel = -1;
    this->is_visible = 1;
}


void TSound_Play(TSound *this, int plays)
{
    if (!this || !this->sound) return;

    this->channel = Mix_PlayChannel(-1, this->sound, plays - 1);
}

void TSound_Stop(TSound *this)
{
    if (!this || !this->sound) return;

    if (this->channel != -1)
        Mix_HaltChannel(this->channel);
}

void TSound_New_Free(TSound *this)
{
    if (this) {
        this->Stop(this);
    }
    free(this);
}

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

#include "cache.h"
#include "resource.h"
#include "window.h"
#include "utils.h"

static void TResourceCache_Init(TResourceCache *this, TWindow *window, unsigned int max_cache);

TResourceCache* New_TResourceCache(TWindow *window, unsigned int max_cache)
{
    TResourceCache *this = malloc(sizeof(TResourceCache));

    if(!this) return (NULL);
    TResourceCache_Init(this, window, max_cache);
    this->Free = TResourceCache_New_Free;
    return (this);
}

static void TResourceCache_Init(TResourceCache *this, TWindow *window, unsigned int max_cache)
{
    if (!this || !window) return;

    this->CacheResource = TResourceCache_CacheResource;
    this->FetchResource = TResourceCache_FetchResource;
    this->ClearCache = TResourceCache_ClearCache;
    this->cache = NULL;
    this->count_cache = 0;
    this->max_caching = max_cache;
    this->window = window;
}

void *TResourceCache_CacheResource(TResourceCache *this, const char *res_path, TResource_Type type)
{
    if (!this || !res_path) return (NULL);

    if (this->count_cache >= this->max_caching) return (NULL);

    void *resource = NULL;
    unsigned int added = 0;

    if (type == GRAPHICAL)
        loadImageResource(this->window, res_path, (SDL_Surface**)&resource, NULL);
    if (type == SHORT_AUDIO)
        resource = (void*)Mix_LoadWAV(res_path);
    if (type == LONG_AUDIO)
        resource = (void*)Mix_LoadMUS(res_path);

    if (!resource) return (NULL);

    if (!this->cache) {
        TResource_Node *res_node = malloc(sizeof(TResource_Node));

        if (res_node) {
            res_node->res_id = hash(res_path);
            res_node->resource = resource;
            res_node->type = type;
            res_node->next = NULL;
            this->cache = res_node;
            this->count_cache++;
            added = 1;
        }
    } else {
        TResource_Node *current = this->cache;

        while (current->next != NULL)
            current = current->next;
        current->next = malloc(sizeof(TResource_Node));
        if (current->next) {
            current->next->res_id = hash(res_path);
            current->next->resource = resource;
            current->next->type = type;
            current->next->next = NULL;
            this->count_cache++;
            added = 1;
        }
    }
    if (!added) {
        if (type == GRAPHICAL)
            SDL_FreeSurface((SDL_Surface*)resource);
        if (type == SHORT_AUDIO)
            Mix_FreeChunk((Mix_Chunk*)resource);
        if (type == LONG_AUDIO)
            Mix_FreeMusic((Mix_Music*)resource);
        resource = NULL;
    }
    return (resource);
}

void *TResourceCache_FetchResource(TResourceCache *this, const char *res_path, TResource_Type type)
{
    if (!this || !res_path) return (NULL);

    TResource_Node *current = this->cache;
    unsigned long uid = hash(res_path);
    void *resource = NULL;

    while (current != NULL) {
        if (current->res_id == uid) {
            if (current->type == GRAPHICAL)
                return SDL_CreateTextureFromSurface(this->window->renderer_window, (SDL_Surface*)current->resource);
            else
                return (current->resource);
        }
        current = current->next;
    }

    resource = this->CacheResource(this, res_path, type);
    if (type != GRAPHICAL)
        return (resource);

    if (!resource) {
        loadImageResource(this->window, res_path, NULL, (SDL_Texture**)&resource);
        return (resource);
    } else
        return SDL_CreateTextureFromSurface(this->window->renderer_window, (SDL_Surface*)resource);
}

void TResourceCache_ClearCache(TResourceCache *this)
{
    if (!this) return;

    TResource_Node *current = this->cache;
    TResource_Node *tmp = NULL;
    while (current != NULL) {
        if (current->resource) {
            if (current->type == GRAPHICAL)
                SDL_FreeSurface((SDL_Surface*)current->resource);
            if (current->type == SHORT_AUDIO)
                Mix_FreeChunk((Mix_Chunk*)current->resource);
            if (current->type == LONG_AUDIO)
                Mix_FreeMusic((Mix_Music*)current->resource);
        }

        tmp = current;
        current = current->next;
        free(tmp);
    }
}

void TResourceCache_New_Free(TResourceCache *this)
{
    if (this) {
        this->ClearCache(this);
    }
    free(this);
}

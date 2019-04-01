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
    this->FetchSurface = TResourceCache_FetchSurface;
    this->FetchTexture = TResourceCache_FetchTexture;
    this->ClearCache = TResourceCache_ClearCache;
    this->cache = NULL;
    this->count_cache = 0;
    this->max_caching = max_cache;
    this->window = window;
}

SDL_Surface *TResourceCache_CacheResource(TResourceCache *this, const char *res_path)
{
    if (!this || !res_path) return (NULL);

    if (this->count_cache >= this->max_caching) return (NULL);

    SDL_Surface *surface;
    unsigned int res_load;
    unsigned int added = 0;

    res_load = loadImageResource(this->window, res_path, &surface, NULL);
    if (!res_load) return (NULL);

    if (!this->cache) {
        TResource_Node *res_node = malloc(sizeof(TResource_Node));

        if (res_node) {
            res_node->res_id = hash(res_path);
            res_node->surface = surface;
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
            current->next->surface = surface;
            current->next->next = NULL;
            this->count_cache++;
            added = 1;
        }
    }
    if (!added) {
        SDL_FreeSurface(surface);
        surface = NULL;
    }
    return (surface);
}

SDL_Surface *TResourceCache_FetchSurface(TResourceCache *this, const char *res_path)
{
    if (!this || !res_path) return (NULL);

    TResource_Node *current = this->cache;
    unsigned long uid = hash(res_path);
    SDL_Surface *surface = NULL;

    while (current != NULL) {
        if (current->res_id == uid) {
            return (current->surface);
        }
        current = current->next;
    }
    surface = this->CacheResource(this, res_path);
    if (!surface)
        loadImageResource(this->window, res_path, &surface, NULL);
    return (surface);
}

SDL_Texture *TResourceCache_FetchTexture(TResourceCache *this, const char *res_path)
{
    if (!this || !res_path) return (NULL);

    TResource_Node *current = this->cache;
    unsigned long uid = hash(res_path);
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;

    while (current != NULL) {
        if (current->res_id == uid) {
            return SDL_CreateTextureFromSurface(this->window->renderer_window, current->surface);
        }
        current = current->next;
    }
    surface = this->CacheResource(this, res_path);
    if (!surface) {
        loadImageResource(this->window, res_path, NULL, &texture);
    } else {
        texture = SDL_CreateTextureFromSurface(this->window->renderer_window, surface);
    }
    return (texture);
}

void TResourceCache_ClearCache(TResourceCache *this)
{
    if (!this) return;

    TResource_Node *current = this->cache;
    TResource_Node *tmp = NULL;
    while (current != NULL) {
        if (current->surface)
            SDL_FreeSurface(current->surface);

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

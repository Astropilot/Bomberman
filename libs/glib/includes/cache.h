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
 * @file cache.h
 * @brief Header file of resource caching manipulation.
 *
 * This file have manipulation functions for resources caching.
 *
 */

#ifndef GLIB_CACHE_H_
#define GLIB_CACHE_H_

#include <SDL2/SDL.h>

typedef struct TWindow TWindow;

/**
 * @brief A linked list for resource caching database.
 *
 * TResource_Node is a linked list for resource caching database.
 */
typedef struct TResource_Node {
    unsigned long res_id;           /*!< The unique ID of the resource. */
    SDL_Surface *surface;           /*!< The SDL surface of the resource. */
    struct TResource_Node *next;    /*!< A pointer to the next TResource_Node. */
} TResource_Node ;

/**
 * @brief Object oriented structure representing a caching util.
 *
 * TResourceCache is an object that allows you to create and manage a resource cache.
 */
typedef struct TResourceCache {

    SDL_Surface*(*CacheResource)(struct TResourceCache*, const char*);

    SDL_Surface*(*FetchSurface)(struct TResourceCache*, const char*);

    SDL_Texture*(*FetchTexture)(struct TResourceCache*, const char*);

    void(*ClearCache)(struct TResourceCache*);

    void(*Free)(struct TResourceCache*);            /*!< Free (ressources) method. */

    TResource_Node *cache;
    unsigned int count_cache;
    unsigned int max_caching;
    TWindow *window;

} TResourceCache ;

TResourceCache* New_TResourceCache(TWindow *window, unsigned int max_cache);
SDL_Surface* TResourceCache_CacheResource(TResourceCache *this, const char *res_path);
SDL_Surface *TResourceCache_FetchSurface(TResourceCache *this, const char *res_path);
SDL_Texture *TResourceCache_FetchTexture(TResourceCache *this, const char *res_path);
void TResourceCache_ClearCache(TResourceCache *this);
void TResourceCache_New_Free(TResourceCache *this);

#endif

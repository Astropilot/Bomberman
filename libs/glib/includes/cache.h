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

    SDL_Surface*(*CacheResource)(struct TResourceCache*, const char*);      /*!< Method for cache a resource. */

    SDL_Surface*(*FetchSurface)(struct TResourceCache*, const char*);       /*!< Method for fetch a resource Surface. */

    SDL_Texture*(*FetchTexture)(struct TResourceCache*, const char*);       /*!< Method for fetch a resource Texture. */

    void(*ClearCache)(struct TResourceCache*);                              /*!< Method for clear the cache. */

    void(*Free)(struct TResourceCache*);                                    /*!< Free (ressources) method. */

    TResource_Node *cache;          /*!< The internal cache database. */
    unsigned int count_cache;       /*!< The amount of resources cached. */
    unsigned int max_caching;       /*!< The maximum amount of resource that can be cached. */
    TWindow *window;                /*!< The window instance. */

} TResourceCache ;

/**
 * @fn TResourceCache* New_TResourceCache(TWindow *window, unsigned int max_cache)
 * @brief The constructor for create a TResourceCache object.
 *
 * @param window A pointer to the window object.
 * @param max_cache The maximum amount of different resources to cache.
 * @return A memory allocated object of the cache manager.
 */
TResourceCache* New_TResourceCache(TWindow *window, unsigned int max_cache);

/**
 * @fn SDL_Surface* TResourceCache_CacheResource(TResourceCache *this, const char *res_path)
 * @brief Method for add to cache a resource.
 *
 * @param this A pointer to the cache manager object.
 * @param res_path The path of the resource to cache.
 * @return Return an SDL_Surface of the resource.
 *
 * You do not have to call this method directly. You must use the
 * CacheResource method of the TResourceCache structure like this:
 * my_cache->CacheResource(my_cache, "images/sample_resource.png");
 */
SDL_Surface* TResourceCache_CacheResource(TResourceCache *this, const char *res_path);

/**
 * @fn SDL_Surface *TResourceCache_FetchSurface(TResourceCache *this, const char *res_path)
 * @brief Method for fetch a resource Surface from cache or a new resource if not cached.
 *
 * @param this A pointer to the cache manager object.
 * @param res_path The path of the resource to cache.
 * @return Return an SDL_Surface of the resource.
 *
 * You do not have to call this method directly. You must use the
 * FetchSurface method of the TResourceCache structure like this:
 * my_cache->FetchSurface(my_cache, "images/sample_resource.png");
 */
SDL_Surface *TResourceCache_FetchSurface(TResourceCache *this, const char *res_path);

/**
 * @fn SDL_Texture *TResourceCache_FetchTexture(TResourceCache *this, const char *res_path)
 * @brief Method for fetch a resource Texture from cache or a new resource if not cached.
 *
 * @param this A pointer to the cache manager object.
 * @param res_path The path of the resource to cache.
 * @return Return an SDL_Texture of the resource.
 *
 * You do not have to call this method directly. You must use the
 * FetchTexture method of the TResourceCache structure like this:
 * my_cache->FetchTexture(my_cache, "images/sample_resource.png");
 */
SDL_Texture *TResourceCache_FetchTexture(TResourceCache *this, const char *res_path);

/**
 * @fn void TResourceCache_ClearCache(TResourceCache *this)
 * @brief Method for clear the cache.
 *
 * @param this A pointer to the cache manager object.
 *
 * You do not have to call this method directly. You must use the
 * ClearCache method of the TResourceCache structure like this:
 * my_cache->ClearCache(my_cache);
 */
void TResourceCache_ClearCache(TResourceCache *this);

/**
 * @fn void TResourceCache_New_Free(TResourceCache *this)
 * @brief Method to free all ressources take by the cache manager.
 *
 * @param this A pointer to the cache manager object.
 *
 * You do not have to call this method directly. You must use the
 * Free method of the TResourceCache structure like this:
 * my_cache->Free(my_cache);
 */
void TResourceCache_New_Free(TResourceCache *this);

#endif

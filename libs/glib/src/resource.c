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
#include <SDL2/SDL_image.h>

#include "resource.h"
#include "window.h"

unsigned int loadImageResource(TWindow *window, const char *path, SDL_Surface **surface, SDL_Texture **texture)
{
    SDL_Surface *tmp_surface;
    SDL_Texture *tmp_texture;

    if (surface) *surface = NULL;
    if (texture) *texture = NULL;
    if (!window || !path || (surface == NULL && texture == NULL)) return (0);
    tmp_surface = IMG_Load(path);

    if (!tmp_surface) return (0);

    if (surface != NULL)
        *surface = tmp_surface;

    if (texture == NULL) return (1);

    tmp_texture = SDL_CreateTextureFromSurface(window->renderer_window, tmp_surface);
    if (!tmp_texture) {
        SDL_FreeSurface(tmp_surface);
        if (surface) *surface = NULL;
        return (0);
    }
    *texture = tmp_texture;
    if (surface == NULL)
        SDL_FreeSurface(tmp_surface);
    return (1);
}

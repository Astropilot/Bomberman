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

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "utils.h"
#include "scene.h"
#include "window.h"

SDL_Texture *createText(TScene *scene, const char *text, TTF_Font *font, SDL_Color color, SDL_Rect *pos)
{
    if (!text || !font || !pos || !scene)
        return (NULL);

    SDL_Surface *s_text = NULL;
    SDL_Texture *text_texture = NULL;

    s_text = TTF_RenderText_Solid(font, text, color);
    if (!s_text) return (NULL);
    text_texture = SDL_CreateTextureFromSurface(scene->window->renderer_window, s_text);
    pos->w = s_text->w;
    pos->h = s_text->h;
    SDL_FreeSurface(s_text);

    return (text_texture);
}

TTF_Font *loadFont(const char *font_file, unsigned int font_size)
{
    if (!font_file) return (NULL);

    TTF_Font *font = NULL;

    font = TTF_OpenFont(font_file, (int)font_size);
    if (!font)
        fprintf(stderr, "[GLib] Unable to load the font %s, reason: %s\n", font_file, TTF_GetError());
    return (font);
}

unsigned long hash(const char *str)
{
    unsigned long hash = 0;

    if (!str) return (hash);
    while (*str != '\0')
        hash = (31 * hash) + (unsigned char)*str++;
    return (hash);
}

/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Source file of the util functions of GLib.
*/

#include <stdio.h>

#include "utils.h"
#include "frame.h"
#include "window.h"

SDL_Texture *createText(TFrame *frame, const char *text, TTF_Font *font, SDL_Color color, SDL_Rect *pos)
{
    if (!text || !font || !pos || !frame)
        return (NULL);

    SDL_Surface *s_text = NULL;
    SDL_Texture *text_texture = NULL;

    s_text = TTF_RenderText_Solid(font, text, color);
    text_texture = SDL_CreateTextureFromSurface(frame->window->renderer_window, s_text);
    pos->w = s_text->w;
    pos->h = s_text->h;
    SDL_FreeSurface(s_text);

    return (text_texture);
}

TTF_Font *loadFont(const char *font_file, size_t font_size)
{
    TTF_Font *font = NULL;

    font = TTF_OpenFont(font_file, font_size);
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

/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** gLib
** File description:
**      Source file of the util functions of GLib.
*/

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
    free(s_text);

    return (text_texture);
}

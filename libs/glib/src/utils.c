#include "utils.h"

#include "window.h"

SDL_Texture *createText(const char *text, TTF_Font *font, SDL_Color color, SDL_Rect *pos, TWindow *win)
{
    SDL_Surface *s_text = NULL;
    SDL_Texture *text_texture = NULL;

    s_text = TTF_RenderText_Solid(font, text, color);
    text_texture = SDL_CreateTextureFromSurface(win->renderer_window, s_text);
    pos->w = s_text->w;
    pos->h = s_text->h;
    free(s_text);

    return (text_texture);
}

#include "utils.h"

SDL_Texture *create_texture(const char *file, TWindow *window)
{
    SDL_Surface *surface = IMG_Load(file);
    SDL_Texture *texture = NULL;

    if (surface == NULL)
        return (NULL);
    texture = SDL_CreateTextureFromSurface(window->renderer_window, surface);
    if (texture == NULL) {
        SDL_FreeSurface(surface);
        return (NULL);
    }
    SDL_FreeSurface(surface);
    return (texture);
}

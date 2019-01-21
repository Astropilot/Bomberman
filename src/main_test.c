#include <stdio.h>
#include <unistd.h>

#include "glib.h"
#include "frame_game.h"
#include "frame_menu.h"

int main(void)
{
    TWindow *window = New_TWindow(); // Constructeur, création de l'objet.
    TFrame *frame_game = New_GameFrame(); // Constructeur, création de l'objet.
    TFrame *frame_menu = New_MenuFrame();

    if (window) {
        window->Add_Frame(window, frame_game);
        window->Add_Frame(window, frame_menu);
        window->Create_Window(window, "Sample #1 GLib", 800, 800, "FRAME_MENU");

        window->Free(window);
        window = NULL;
    } else {
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}

#include <stdio.h>
#include <unistd.h>

#include "glib.h"
#include "frame_test.h"

int main(void)
{
    TWindow *window = New_TWindow(); // Constructeur, création de l'objet.
    TFrame *frame_test = New_TestFrame(); // Constructeur, création de l'objet.

    if (window) {
        window->Add_Frame(window, frame_test);
        window->Create_Window(window, "Sample #1 GLib", 600, 300, "FRAME_TEST");

        window->Free(window);
        window = NULL;
    } else {
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}

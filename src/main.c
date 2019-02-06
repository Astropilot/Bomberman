/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the main program that starts the game.
*/

#include <stdio.h>
#include <unistd.h>

#include "main.h"
#include "glib.h"
#include "frame_game.h"
#include "frame_main_menu.h"
#include "frame_host_menu.h"
#include "frame_join_menu.h"

int main(void)
{
    TWindow *window = New_TWindow();
    TFrame *frame_game = New_GameFrame();
    TFrame *frame_main_menu = New_MainMenuFrame();
    TFrame *frame_host_menu = New_HostMenuFrame();
    TFrame *frame_join_menu = New_JoinMenuFrame();

    if (window) {
        window->Add_Frame(window, frame_game);
        window->Add_Frame(window, frame_main_menu);
        window->Add_Frame(window, frame_host_menu);
        window->Add_Frame(window, frame_join_menu);
        window->Create_Window(window, "Bomberman", WIN_WIDTH, WIN_HEIGHT, "FRAME_MAIN_MENU", 30);

        window->Free(window);
        window = NULL;
    } else {
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}

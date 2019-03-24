/*
** ETNA PROJECT, 28/01/2019 by martin_h, hamide_a, despla_g, weber_w
** Bomberman
** File description:
**      Source file of the main program that starts the game.
*/

#include "main.h"
#include "glib.h"
#include "ui/frame_game.h"
#include "ui/frame_main_menu.h"
#include "ui/frame_host_menu.h"
#include "ui/frame_join_menu.h"
#include "ui/frame_lobby.h"
#include "network/network.h"
#include "network/game/client.h"
#include "network/game/lobby.h"

int main(void)
{
    TLobbyClient *lobbyclient = New_TLobbyClient();
    TGameClient *gameclient = New_TGameClient();
    TWindow *window = New_TWindow();
    TFrame *frame_main_menu = New_MainMenuFrame();
    TFrame *frame_host_menu = New_HostMenuFrame();
    TFrame *frame_join_menu = New_JoinMenuFrame();
    TFrame *frame_lobby = New_LobbyFrame(lobbyclient);
    TFrame *frame_game = New_GameFrame(gameclient);
    int process_result = EXIT_SUCCESS;

    InitNetworking();
    if (window) {
        window->Add_Frame(window, frame_main_menu);
        window->Add_Frame(window, frame_host_menu);
        window->Add_Frame(window, frame_join_menu);
        window->Add_Frame(window, lobbyclient->Register_Frame(lobbyclient, frame_lobby));
        window->Add_Frame(window, gameclient->Register_Frame(gameclient, frame_game));
        window->Create_Window(window, "Bomberman", WIN_WIDTH, WIN_HEIGHT, "FRAME_MAIN_MENU", 30);

        window->Free(window);
        window = NULL;
    } else
        process_result = EXIT_FAILURE;

    ResetNetworking();
    return (process_result);
}

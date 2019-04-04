/*******************************************************************************
* PROJECT: Bomberman
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

#include "main.h"
#include "glib.h"
#include "ui/frame_game.h"
#include "ui/frame_main_menu.h"
#include "ui/frame_host_menu.h"
#include "ui/frame_join_menu.h"
#include "ui/frame_lobby.h"
#include "ui/frame_end_game.h"
#include "network/network.h"
#include "network/game/client.h"
#include "network/game/lobby.h"

int main(void)
{
    TLobbyClient *lobbyclient = New_TLobbyClient();
    TGameClient *gameclient = New_TGameClient();
    TWindow *window = New_TWindow(134);
    TFrame *frame_main_menu = New_MainMenuFrame();
    TFrame *frame_host_menu = New_HostMenuFrame();
    TFrame *frame_join_menu = New_JoinMenuFrame();
    TFrame *frame_lobby = New_LobbyFrame(lobbyclient);
    TFrame *frame_game = New_GameFrame(gameclient);
    TFrame *frame_end_game = New_EndGameFrame();
    int process_result = EXIT_SUCCESS;

    InitNetworking();
    if (window) {
        window->Add_Frame(window, frame_main_menu);
        window->Add_Frame(window, frame_host_menu);
        window->Add_Frame(window, frame_join_menu);
        window->Add_Frame(window, lobbyclient->Register_Frame(lobbyclient, frame_lobby));
        window->Add_Frame(window, gameclient->Register_Frame(gameclient, frame_game));
        window->Add_Frame(window, frame_end_game);
        window->Create_Window(window, "Bomberman", WIN_WIDTH, WIN_HEIGHT, "FRAME_MAIN_MENU", 30);

        window->Free(window);
        window = NULL;
    } else
        process_result = EXIT_FAILURE;

    ResetNetworking();
    return (process_result);
}

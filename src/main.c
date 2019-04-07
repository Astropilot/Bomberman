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
#include "ui/scene_game.h"
#include "ui/scene_main_menu.h"
#include "ui/scene_host_menu.h"
#include "ui/scene_join_menu.h"
#include "ui/scene_lobby.h"
#include "ui/scene_end_game.h"
#include "network/network.h"
#include "network/game/client.h"
#include "network/game/lobby.h"

int main(void)
{
    TLobbyClient *lobbyclient = New_TLobbyClient();
    TGameClient *gameclient = New_TGameClient();
    TWindow *window = New_TWindow(134);
    TScene *scene_main_menu = New_MainMenuScene();
    TScene *scene_host_menu = New_HostMenuScene();
    TScene *scene_join_menu = New_JoinMenuScene();
    TScene *scene_lobby = New_LobbyScene(lobbyclient);
    TScene *scene_game = New_GameScene(gameclient);
    TScene *scene_end_game = New_EndGameScene();
    int process_result = EXIT_SUCCESS;

    InitNetworking();
    if (window) {
        window->Add_Scene(window, scene_main_menu);
        window->Add_Scene(window, scene_host_menu);
        window->Add_Scene(window, scene_join_menu);
        window->Add_Scene(window, lobbyclient->Register_Scene(lobbyclient, scene_lobby));
        window->Add_Scene(window, gameclient->Register_Scene(gameclient, scene_game));
        window->Add_Scene(window, scene_end_game);
        window->Create_Window(window, "Bomberman", WIN_WIDTH, WIN_HEIGHT, "SCENE_MAIN_MENU", 30);

        window->Free(window);
        window = NULL;
    } else
        process_result = EXIT_FAILURE;

    ResetNetworking();
    return (process_result);
}

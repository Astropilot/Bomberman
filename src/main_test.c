#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "glib.h"
#include "frame_game.h"
#include "frame_menu.h"
#include "main.h"

#include "reslib.h"

#define BUF_SIZE 4096


void client_code(void);
void server_code(void);

int main()
{
    TWindow *window = New_TWindow();
    TFrame *frame_game = New_GameFrame();
    TFrame *frame_menu = New_MenuFrame();

    if (window) {
        window->Add_Frame(window, frame_game);
        window->Add_Frame(window, frame_menu);
        window->Create_Window(window, "Bomberman", WIN_WIDTH, WIN_HEIGHT, "FRAME_MENU");

        window->Free(window);
        window = NULL;
    } else {
        return (EXIT_FAILURE);
    }

    /*int choix = 0;
    printf("Mode server 0, Mode client 1: ");
    scanf("%d\n", &choix);
    if (choix == 1) {
        client_code();
    } else {
        server_code();
    }*/

    return (EXIT_SUCCESS);
}

void client_code(void)
{
    char buffer[BUF_SIZE];
    char serverip[255];
    int serverport;
    fd_set rdfs;
    TClient *client = New_TClient();

    printf("Entrez l'ip du serveur: ");
    scanf("%s", serverip);

    printf("\nEntrez le port du serveur: ");
    scanf("%d", &serverport);

    int resconnexion = client->Connect(client, serverip, serverport);

    if (resconnexion == 0) {
        while(1) {
            printf("Hello Ping!\n");
            FD_ZERO(&rdfs);

            FD_SET(STDIN_FILENO, &rdfs);

            if(select(STDIN_FILENO + 1, &rdfs, NULL, NULL, NULL) == -1) {
                perror("select()");
                exit(EXIT_FAILURE);
            }

            if(FD_ISSET(STDIN_FILENO, &rdfs)) {
                fgets(buffer, BUF_SIZE - 1, stdin);
                {
                    char *p = NULL;
                    p = strstr(buffer, "\n");
                    if(p != NULL)
                        *p = 0;
                    else
                        buffer[BUF_SIZE - 1] = 0;
                }
                client->Send(client, buffer, strlen(buffer));
            }
        }
    } else {
        printf("Connexion error\n");
    }

    client->Disconnect(client);
    client->Free(client);
}

void server_code(void)
{

}

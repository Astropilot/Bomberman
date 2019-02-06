#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "reslib.h"

void client_code(void);
void server_code(void);

int main(void)
{
    int choix;

    printf("Merci de choisir 0 pour client et 1 pour serveur: \n");
    scanf("%d", &choix);

    if (choix == 1)
        server_code();
    else
        client_code();

    return 0;
}

/************************** CLIENT PART ************************************/

void Client_On_Message(TClient *client, TMessage message)
{
    if (!client) {
        printf("\n[Client][On_Message] Error\n");
        return;
    }
    if (message.len) {
        printf("\n[Client][On_Message] Receved message [%d]\"%s\"\n", message.len, message.message);
    } else
        printf("\n[Client][On_Message] Client Disconnect\n");
    if (message.len == -1)
        printf("\n[Client][On_Message] Recv error !\n");
}

void client_code(void)
{
    char buffer[128];
    char serverip[255];
    int serverport;
    unsigned int keep_alive = 1;
    TClient *client = New_TClient();
    client->On_Message = Client_On_Message;

    printf("\n[Client] Entrez l'ip du serveur: ");
    scanf("%s", serverip);

    printf("\n[Client] Entrez le port du serveur: ");
    scanf("%d", &serverport);

    int resconnexion = client->Connect(client, serverip, serverport);

    if (resconnexion == 0) {
        client->Start_Recv(client, NULL);
        while(keep_alive) {
            //printf("[Client] Entrez une commande: ");
            fgets(buffer, 128, stdin);
            if ((strlen(buffer) > 0) && (buffer[strlen (buffer) - 1] == '\n'))
                buffer[strlen (buffer) - 1] = '\0';

            TMessage message = {strlen(buffer), buffer};
            client->Send(client, message);
            printf("\n[Client] Sended message [%d]\"%s\" to server\n", (int)strlen(buffer), buffer);
            if (strcmp(buffer, "exit") == 0) {
                keep_alive = 0;
                client->Disconnect(client);
                //client->Stop_Recv(client);
            }
        }
    } else {
        printf("\nConnexion error\n");
    }

    client->Free(client);
}

/************************* SERVER PART *************************************/

void Server_On_Connect(TServer *server, TClient *client)
{
    if (client && server)
        printf("\n[Server][On_Connect] New client ! Actual client count: %d\n", (int)server->CountClients(server));
    else
        printf("\n[Server][On_Connect] Error on connect\n");
}

void Server_On_Message(TServer *server, TClient *client, TMessage message)
{
    if (!server || !client) {
        printf("\n[Server][On_Message] Error\n");
        return;
    }
    if (message.len) {
        printf("\n[Server][On_Message] Receved message [%d]\"%s\"\n", message.len, message.message);
        if (strcmp(message.message, "ping") == 0) {
            char buffer_message[] = "pong";
            TMessage message = {strlen(buffer_message), buffer_message};
            client->Send(client, message);
            printf("\n[Server][On_Message] Sended message [%d]\"%s\" to client\n", (int)strlen(buffer_message), buffer_message);
        }
    } else
        printf("\n[Server][On_Message] Client Disconnect\n");
    if (message.len == -1)
        printf("\n[Server][On_Message] Recv error !\n");
}

void Server_On_Disconnect(TServer *server, TClient *client)
{
    if (client && server)
        printf("\n[Server][On_Disconnect] Client leave ! Actual client count: %d\n", (int)server->CountClients(server));
    else
        printf("\n[Server][On_Disconnect] Error on disconnect\n");
}

void server_code(void)
{
    char buffer[128];
    int servermax_c;
    int serverport;
    unsigned int keep_alive = 1;
    TServer *server = NULL;

    printf("\n[Server] Entrez le port du serveur: ");
    scanf("%d", &serverport);

    printf("\n[Server] Entrez le maximum de clients: ");
    scanf("%d", &servermax_c);

    server = New_TServer(serverport, servermax_c);
    server->On_Connect = Server_On_Connect;
    server->On_Message = Server_On_Message;
    server->On_Disconnect = Server_On_Disconnect;

    server->Start_Listenning(server);
    while(keep_alive) {
        //printf("[Server] Entrez une commande: ");
        fgets(buffer, 128, stdin);
        if ((strlen(buffer) > 0) && (buffer[strlen (buffer) - 1] == '\n'))
            buffer[strlen (buffer) - 1] = '\0';

        if (strcmp(buffer, "exit") == 0) {
            keep_alive = 0;
            server->Stop_Listenning(server);
        }
        TMessage message = {strlen(buffer), buffer};
        server->Send_Broadcast(server, message);
        printf("\n[Server] Sended message [%d]\"%s\" to all clients\n", (int)strlen(buffer), buffer);
    }

    server->Free(server);
}

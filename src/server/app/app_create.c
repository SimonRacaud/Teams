/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 app_create.c
*/

#include "server.h"
#include "socket.h"
#include "utility.h"
#include <signal.h>
#include "database.h"

static void client_list_init(server_t *server)
{
    MY_LIST_INIT(server->clients);
    LIST_INIT((&server->clients));
}

int app_create(server_t *server, uint port)
{
    if (signal_manager(SIGINT, &server->loop) == EXIT_FAILURE) {
        printf("signal_manager: fail\n");
        return EXIT_FAILURE;
    }
    if (socket_server_create(&server->socket, port, SERVER_MAX_CLIENT)) {
        printf("socket_server_create: fail\n");
        return EXIT_FAILURE;
    }
    client_list_init(server);
    if (!load_database(&server->database)) {
        printf("load_database: fail\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
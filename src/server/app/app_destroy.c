/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 app_destroy.c
*/

#include "server.h"
#include "database.h"

static void client_list_destroy(client_list_t *list_ptr)
{
    client_t *ptr = LIST_FIRST(list_ptr);
    client_t *ptr_next;

    while (ptr != NULL) {
        ptr_next = LIST_NEXT(ptr, entries);
        socket_close(&ptr->socket);
        free(ptr);
        ptr = ptr_next;
    }
    LIST_INIT(list_ptr);
}

int app_destroy(server_t *server)
{
    if (socket_close(&server->socket)) {
        destroy_database_t(&server->database);
        return EXIT_FAILURE;
    }
    client_list_destroy(&server->clients);
    if (!save_database(&server->database)) {
        destroy_database_t(&server->database);
        return EXIT_FAILURE;
    }
    destroy_database_t(&server->database);
    return EXIT_SUCCESS;
}
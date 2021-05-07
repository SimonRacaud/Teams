/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 app_loop.c
*/

#include "server.h"

static int process_read(server_t *server)
{
    client_t *ptr;

    if (FD_READ_ISSET(server, server)) {
        if (connect_client(server) == EXIT_FAILURE)
            return EXIT_FAILURE;
    }
    LIST_FOREACH(ptr, (&server->clients), entries) {
        if (FD_READ_ISSET(ptr, server)) {
            // process_request(server, ptr)
        }
    }
    return EXIT_SUCCESS;
}

static int process_write(server_t *server)
{
    response_t *ptr = SLIST_FIRST(&server->responses);
    response_t *ptr_next;

    while (ptr != NULL) {
        ptr_next = SLIST_NEXT(ptr, entries);
        if (FD_WRITE_ISSET(ptr, server)) {
            // send_response(server, ptr)
            SLIST_REMOVE(&server->responses, ptr, response_s, entries);
            free(ptr);
        }
        ptr = ptr_next;
    }
    return EXIT_SUCCESS;
}

int app_loop(server_t *server)
{
    while (server->loop) {
        if (app_select(server) == EXIT_FAILURE)
            return EXIT_FAILURE;
        if (process_read(server) == EXIT_FAILURE)
            return EXIT_FAILURE;
        if (process_write(server) == EXIT_FAILURE)
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
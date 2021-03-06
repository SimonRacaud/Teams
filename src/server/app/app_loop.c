/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 app_loop.c
*/

#include "server.h"

static int process_read(server_t *server)
{
    client_t *ptr = LIST_FIRST(&server->clients);
    client_t *ptr_next = NULL;

    if (FD_READ_ISSET(server, server)) {
        if (connect_client(server) == EXIT_FAILURE)
            return EXIT_FAILURE;
    }
    while (ptr != NULL) {
        ptr_next = LIST_NEXT(ptr, entries);
        if (FD_READ_ISSET(ptr, server)
            && process_request(server, ptr)) {
            return EXIT_FAILURE;
        }
        ptr = ptr_next;
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
            if (response_send(ptr) == EXIT_FAILURE) {
                printf("ERROR: send_response failed\n");
            }
            SLIST_REMOVE(&server->responses, ptr, response_s, entries);
            response_destroy(ptr);
        }
        ptr = ptr_next;
    }
    return EXIT_SUCCESS;
}

int app_loop(server_t *server)
{
    while (server->loop) {
        if (app_select(server) == EXIT_FAILURE) {
            return EXIT_SUCCESS;
        }
        if (process_read(server) == EXIT_FAILURE) {
            printf("process_read: fail\n");
            return EXIT_FAILURE;
        }
        if (process_write(server) == EXIT_FAILURE) {
            printf("process_write: fail\n");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
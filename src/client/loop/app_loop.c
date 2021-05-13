/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 app_loop.c
*/

#include "client.h"

static int app_select(
    select_t *select, socket_t *socket, request_stack_t *stack)
{
    if (SLIST_EMPTY(stack)) {
        return fd_select(select, 2, 0, socket->fd, STDIN_FILENO);
    } else {
        return fd_select(select, 2, 1, socket->fd, STDIN_FILENO, socket->fd);
    }
}

int app_loop(client_t *client)
{
    while (client->loop) {
        if (app_select(&client->select, &client->socket, &client->stack))
            return EXIT_FAILURE;
        if (process_read(client) == EXIT_FAILURE)
            return EXIT_FAILURE;
        if (process_write(client) == EXIT_FAILURE)
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
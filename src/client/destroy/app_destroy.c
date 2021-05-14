/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 app_destroy.c
*/

#include "client.h"

static void stack_destroy(request_stack_t *stack)
{
    request_t *ptr;

    while (!SLIST_EMPTY(stack)) {
        ptr = SLIST_FIRST(stack);
        SLIST_REMOVE_HEAD(stack, entries);
        request_destroy(ptr);
    }
}

int app_destroy(client_t *client)
{
    if (socket_close(&client->socket) == EXIT_FAILURE)
        return EXIT_FAILURE;
    stack_destroy(&client->stack);
    if (client->cli_buffer) {
        free(client->cli_buffer);
    }
    return EXIT_SUCCESS;
}
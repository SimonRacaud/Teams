/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 process_write.c
*/

#include "client.h"

int process_write(client_t *client)
{
    request_t *ptr = NULL;

    if (!FD_ISSET(client->socket.fd, &client->select.write_fds)) {
        return EXIT_SUCCESS;
    }
    while (!SLIST_EMPTY(&client->stack)) {
        ptr = SLIST_FIRST(&client->stack);
        SLIST_REMOVE_HEAD(&client->stack, entries);
        if (request_write(ptr) == EXIT_FAILURE) {
            printf("ERROR: fail to send request\n");
        }
        request_destroy(ptr);
    }
    return EXIT_SUCCESS;
}
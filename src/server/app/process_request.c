/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 process_request.c
*/

#include "server.h"

request_t *get_request(client_t *client, bool *cancel)
{
    request_t *request = NULL;
    bool is_empty = false;
    char *input = fd_getline_delim(
        client->socket.fd, &client->read_buffer, END_COM, &is_empty);

    if (!input && is_empty) {
        disconnect_client(client);
        *cancel = true;
        return NULL;
    } else if (!input) {
        return NULL;
    }
    request = request_create(input);
    free(input);
    if (!request) {
        printf("ERROR: invalid input command\n");
        return NULL;
    }
    return request;
}

int process_request(server_t *server, client_t *client)
{
    request_t *request = NULL;
    bool cancel = false;

    request = get_request(client, &cancel);
    if (cancel) {
        return EXIT_SUCCESS;
    } else if (!request) {
        return EXIT_FAILURE;
    }
    if (request_execute(request, server, client) == EXIT_FAILURE)
        return EXIT_FAILURE;
    request_destroy(request);
    return EXIT_SUCCESS;
}
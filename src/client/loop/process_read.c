/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 process_read.c
*/

#include "client.h"
#include "logger.h"
#include <sys/select.h>

static int process_cli(client_t *client)
{
    bool disconnect = false;
    char *input = NULL;
    request_t *request = NULL;

    input = prompt(&client->cli_buffer, &disconnect);
    if (disconnect) {
        client->loop = false;
        return EXIT_SUCCESS;
    } else if (!input) {
        return EXIT_SUCCESS;
    }
    request = request_create(input);
    free(input);
    if (!request) {
        printf("ERROR: invalid command\n");
        return EXIT_SUCCESS;
    }
    request_push(&client->stack, request, &client->socket);
    return EXIT_SUCCESS;
}

static int process_response(client_t *client)
{
    response_t *response = NULL;

    response = response_read(client->socket.fd, &client->response_buffer);
    if (response == NULL) {
        client->response_buffer.buff = NULL;
        printf("ERROR: fail to read response\n");
        return EXIT_SUCCESS;
    }
    if (logger(response) == EXIT_FAILURE)
        return EXIT_FAILURE;
    response_destroy(response);
    return EXIT_SUCCESS;
}

int process_read(client_t *client)
{
    if (FD_ISSET(client->socket.fd, &client->select.read_fds)) {
        if (process_response(client) == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }
    }
    if (FD_ISSET(STDIN_FILENO, &client->select.read_fds)) {
        if (process_cli(client) == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
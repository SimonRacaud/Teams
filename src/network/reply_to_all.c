/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 22/05/2021 reply_to_all.c
*/

#include "network.h"

int reply_to_all(server_t *server, request_t *request, void *body)
{
    response_t *response;
    client_t *client;
    void *res_body;

    if (!body)
        return EXIT_FAILURE;
    LIST_FOREACH(client, &server->clients, entries) {
        if (client->user_ptr != NULL) {
            res_body = dup_body(body);
            response =
                response_create(SUCCESS, request, &client->socket, res_body);
            response_push(server, response);
        }
    }
    free(body);
    return EXIT_SUCCESS;
}
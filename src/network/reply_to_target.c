/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 22/05/2021 reply_to_target.c
*/

#include "network.h"

int reply_to_target(
    server_t *server, request_t *request, void *body, user_t *user)
{
    socket_t *sock = get_socket_user(server, user);
    response_t *response;

    if (!sock)
        return EXIT_SUCCESS;
    response = response_create(SUCCESS, request, sock, body);
    if (!response) {
        return EXIT_FAILURE;
    }
    response_push(server, response);
    return EXIT_SUCCESS;
}

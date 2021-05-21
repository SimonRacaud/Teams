/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 17/05/2021 reply.c
*/

#include "network.h"
#include "uuid_selector_t.h"

int reply_target(
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
    if (response_send(response) == EXIT_FAILURE) {
        response_destroy(response);
        return EXIT_FAILURE;
    }
    response_destroy(response);
    return EXIT_SUCCESS;
}

int reply(
    rcode_e code, request_t *request, void *body, uuid_selector_t *params)
{
    response_t *response;
    uuid_t uuid;

    if (code != SUCCESS) {
        free(body);
        get_err_target(&uuid, params, code);
        return reply_error(code, request, uuid);
    }
    response = response_create(code, request, request->receiver, body);
    if (!response) {
        return EXIT_FAILURE;
    }
    if (response_send(response) == EXIT_FAILURE) {
        response_destroy(response);
        return EXIT_FAILURE;
    }
    response_destroy(response);
    return EXIT_SUCCESS;
}

int reply_str(rcode_e code, request_t *request, const char *str)
{
    void *body = body_maker_string(str);
    response_t *response;

    if (!body)
        return EXIT_FAILURE;
    response = response_create(code, request, request->receiver, body);
    if (!response) {
        return EXIT_FAILURE;
    }
    if (response_send(response) == EXIT_FAILURE) {
        response_destroy(response);
        return EXIT_FAILURE;
    }
    response_destroy(response);
    return EXIT_SUCCESS;
}

int reply_error(rcode_e code, request_t *request, uuid_t target)
{
    response_t *response;
    void *body = body_maker_uuid(target, LOG_T_ERROR);

    if (!body)
        return EXIT_FAILURE;
    response = response_create(code, request, request->receiver, body);
    if (!response) {
        return EXIT_FAILURE;
    }
    if (response_send(response) == EXIT_FAILURE) {
        response_destroy(response);
        return EXIT_FAILURE;
    }
    response_destroy(response);
    return EXIT_SUCCESS;
}
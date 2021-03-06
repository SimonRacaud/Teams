/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 17/05/2021 reply.c
*/

#include "network.h"
#include "uuid_selector_t.h"

int reply(rerr_t error, request_t *request, void *body, server_t *server)
{
    response_t *response;
    uuid_t uuid;

    if (request && error.code != SUCCESS) {
        free(body);
        get_err_target(&uuid, error.select, error.code);
        return reply_error(server, error.code, request, &uuid);
    }
    if (!request || !body)
        return EXIT_FAILURE;
    response = response_create(error.code, request, request->receiver, body);
    if (!response) {
        return EXIT_FAILURE;
    }
    response_push(server, response);
    return EXIT_SUCCESS;
}

int reply_str(
    server_t *server, rcode_e code, request_t *request, const char *str)
{
    void *body = body_maker_string(str);
    response_t *response;

    if (!body)
        return EXIT_FAILURE;
    response = response_create(code, request, request->receiver, body);
    if (!response) {
        return EXIT_FAILURE;
    }
    response_push(server, response);
    return EXIT_SUCCESS;
}

int reply_error(
    server_t *server, rcode_e code, request_t *request, uuid_t *target)
{
    response_t *response;
    void *body;
    uuid_t arg = {0};

    if (target)
        uuid_copy(arg, *target);
    body = body_maker_uuid(arg, LOG_T_ERROR);
    if (!body)
        return EXIT_FAILURE;
    response = response_create(code, request, request->receiver, body);
    if (!response) {
        return EXIT_FAILURE;
    }
    response_push(server, response);
    return EXIT_SUCCESS;
}
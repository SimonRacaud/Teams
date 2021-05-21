/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 17/05/2021 reply.c
*/

#include "network.h"

int reply(rcode_e code, request_t *request, void *body)
{
    response_t *response =
        response_create(code, request, request->receiver, body);

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

    if (!body)
        return EXIT_FAILURE;
    return reply(code, request, body);
}

int reply_error(rcode_e code, request_t *request, uuid_t target)
{
    void *body = body_maker_uuid(target, "error");

    if (!body)
        return EXIT_FAILURE;
    return reply(code, request, body);
}
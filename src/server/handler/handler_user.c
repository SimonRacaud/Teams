/*
** EPITECH PROJECT, 2021
** handler_user.c
** File description:
** handler_user function
*/

#include "server.h"
#include "database.h"
#include "utility.h"
#include "request_handler_t.h"

static int send_result(user_t *user, request_t *request)
{
    void *body = body_maker_user(user, false);

    if (!body)
        return EXIT_FAILURE;
    return reply(SUCCESS, request, body);
}

int handler_user(server_t *srv, request_t *request, UNUSED client_t *client)
{
    uuid_selector_t select = {0};
    user_t *user = NULL;

    if (!srv || !request)
        return EXIT_FAILURE;
    if (walen(request->args) != 1) {
        return reply_str(ERROR, request, "Invalid argument count");
    }
    if (uuid_parse(request->args[0], select.uuid_user) == -1) {
        return reply_str(ERROR, request, "Invalid argument");
    }
    user = get_user(&srv->database, &select);
    if (!user) {
        return reply_str(ERR_UNKNOWN_USER, request, "Unknown user");
    }
    return send_result(user, request);
}
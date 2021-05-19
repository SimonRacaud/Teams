/*
** EPITECH PROJECT, 2021
** handler_send.c
** File description:
** handler_send function
*/

#include "server.h"
#include "database.h"
#include "request_handler_t.h"

static bool is_correct_arg(request_t *request)
{
    if (get_arg_size((const char **) request->args) == 2) {
        if (strlen(request->args[0]) + 1 == 16) {
            return true;
        }
    }
    return false;
}

static bool generate_msg(database_t *db, request_t *request)
{
    uuid_selector_t params = {0};
    user_t *sender = request->receiver;
    int ret = SUCCESS;

    if (!sender)
        return false;
    get_uuid_from_string(params.uuid_user, request->args[0]);
    ret = create_private_msg(db, request->args[1], sender, &params);
    return (ret == SUCCESS);
}

static response_t *get_response(server_t *srv, request_t *request)
{
    response_t *resp = NULL;

    if (is_correct_arg(request)) {
        if (generate_msg(&srv->database, request))
            resp = response_create(SUCCESS, request, request->receiver, NULL);
        else
            resp = response_create(ERR_UNKNOWN_USER, request, request->receiver, NULL);
    } else {
        resp = response_create(ERROR, request, request->receiver, NULL);
    }
    return resp;
}

int handler_send(server_t *srv, request_t *request)
{
    response_t *response = NULL;
    int return_value = 0;

    if (!srv || !request)
        return EXIT_FAILURE;
    response = get_response(srv, request);
    if (!response)
        return EXIT_FAILURE;
    return_value = response_send(response);
    response_destroy(response);
    return return_value;
}
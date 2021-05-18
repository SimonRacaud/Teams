/*
** EPITECH PROJECT, 2021
** handler_user.c
** File description:
** handler_user function
*/

#include "server.h"
#include "database.h"
#include "request_handler_t.h"

static bool is_correct_arg(database_t *db,
request_t *req, int *err, user_t **user)
{
    uuid_t uuid;

    if (get_arg_size((const char **) req->args) == 1) {
        if (strlen(req->args[0]) + 1 == 16) {
            get_uuid_from_string(uuid, req->args[0]);
            *user = get_user_from_uuid(db, uuid);
            *err = ERR_UNKNOWN_USER;
            return (*user) ? true : false;
        } else {
            *err = ERROR;
            return false;
        }
    } else {
        *err = ERROR;
        return false;
    }
}

static char *get_users_data(user_t *user)
{
    char *str = NULL;

    asprintf(&str, "Username: %s\nUuid: %s", user->username, user->uuid);
    return str;
}

static void *get_body(user_t *user)
{
    body_header_t body_struct = {0};
    const char type[] = "string";
    char *data = get_users_data(user);
    void *body = NULL;

    if (!data)
        return NULL;
    body = malloc(sizeof(body_header_t) + strlen(data) + 1);
    if (!body)
        return NULL;
    body_struct.list_size = 1;
    body_struct.elem_size = strlen(data) + 1;
    memcpy(body_struct.type, type, strlen(type));
    memcpy(body, &body_struct, sizeof(body_header_t));
    memcpy(body + sizeof(body_header_t), data, body_struct.elem_size);
    free(data);
    return body;
}

static response_t *get_response(server_t *srv, request_t *request)
{
    user_t *user = NULL;
    response_t *response = NULL;
    int err = ERROR;
    void *body = NULL;

    if (is_correct_arg(&srv->database, request, &err, &user)) {
        body = get_body(user);
        if (!body)
            return NULL;
        response = response_create(SUCCESS, request, request->receiver, body);
    } else {
        response = response_create(err, request, request->receiver, NULL);
    }
    return response;
}

int handler_user(server_t *srv, request_t *request)
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
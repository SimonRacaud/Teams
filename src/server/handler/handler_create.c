/*
** EPITECH PROJECT, 2021
** handler_create.c
** File description:
** handler_create function
*/

#include "server.h"
#include "utility.h"
#include "database.h"
#include "request_handler_t.h"

static int create_team_manage(server_t *srv,
request_t *request, client_t *client)
{
    uuid_selector_t params = {0};
    int err = SUCCESS;

    if (walen(request->args) != 2)
        return reply_str(ERROR, request, "Invalid argument count");
    uuid_copy(params.uuid_user, client->user_ptr->uuid);
    err =
    create_team(&srv->database, request->args[0], request->args[1], &params);
    return reply_str(err, request, (err == SUCCESS) ? "OK" : "KO");
}

static int create_channel_manage(server_t *srv,
request_t *request, client_t *client)
{
    uuid_selector_t params = {0};
    int err = SUCCESS;

    if (walen(request->args) != 2)
        return reply_str(ERROR, request, "Invalid argument count");
    uuid_copy(params.uuid_user, client->user_ptr->uuid);
    uuid_copy(params.uuid_team, client->selector.team);
    err =
    create_channel(&srv->database, request->args[0], request->args[1], &params);
    return reply_str(err, request, (err == SUCCESS) ? "OK" : "KO");
}

static int create_thread_manage(server_t *srv,
request_t *request, client_t *client)
{
    uuid_selector_t params = {0};
    int err = SUCCESS;

    if (walen(request->args) != 2)
        return reply_str(ERROR, request, "Invalid argument count");
    uuid_copy(params.uuid_user, client->user_ptr->uuid);
    uuid_copy(params.uuid_team, client->selector.team);
    uuid_copy(params.uuid_channel, client->selector.channel);
    err =
    create_thread(&srv->database, request->args[0], request->args[1], &params);
    return reply_str(err, request, (err == SUCCESS) ? "OK" : "KO");
}

static int create_reply_manage(server_t *srv,
request_t *request, client_t *client)
{
    uuid_selector_t params = {0};
    int err = SUCCESS;

    if (walen(request->args) != 1)
        return reply_str(ERROR, request, "Invalid argument count");
    uuid_copy(params.uuid_user, client->user_ptr->uuid);
    uuid_copy(params.uuid_team, client->selector.team);
    uuid_copy(params.uuid_channel, client->selector.channel);
    uuid_copy(params.uuid_thread, client->selector.thread);
    err =
    create_reply(&srv->database, client->user_ptr, request->args[0], &params);
    return reply_str(err, request, (err == SUCCESS) ? "OK" : "KO");
}

int handler_create(server_t *srv, request_t *request, client_t *client)
{
    if (!uuid_is_null(client->selector.thread))
        return create_reply_manage(srv, request, client);
    if (!uuid_is_null(client->selector.channel))
        return create_thread_manage(srv, request, client);
    if (!uuid_is_null(client->selector.team))
        return create_channel_manage(srv, request, client);
    return create_team_manage(srv, request, client);
}
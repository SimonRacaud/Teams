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
    void *body = NULL;
    uuid_selector_t params = {0};
    int err = SUCCESS;

    if (walen(request->args) != 2)
        return reply_str(ERROR, request, "Invalid argument count");
    uuid_copy(params.uuid_user, client->user_ptr->uuid);
    err =
    create_team(&srv->database, request->args[0], request->args[1], &params);
    body =
    body_maker_team(get_team(&srv->database, &params), false, LOG_T_EVT_TEAM);
    if (!body)
        return EXIT_FAILURE;
    return reply(err, request, body);
}

static int create_channel_manage(server_t *srv,
request_t *request, client_t *client)
{
    void *body = NULL;
    uuid_selector_t params = {0};
    int err = SUCCESS;

    if (walen(request->args) != 2)
        return reply_str(ERROR, request, "Invalid argument count");
    uuid_copy(params.uuid_user, client->user_ptr->uuid);
    uuid_copy(params.uuid_team, client->selector.team);
    if (!is_subscribed(client, client->selector.team))
        return reply_str(ERROR, request, "You need to be subscribed");
    err =
    create_channel(&srv->database, request->args[0], request->args[1], &params);
    body = body_maker_channel(
        get_channel(&srv->database, &params), false, LOG_T_EVT_CHAN);
    if (!body)
        return EXIT_FAILURE;
    return reply(err, request, body);
}

static int create_thread_manage(server_t *srv,
request_t *request, client_t *client)
{
    void *body = NULL;
    uuid_selector_t params = {0};
    int err = SUCCESS;

    if (walen(request->args) != 2)
        return reply_str(ERROR, request, "Invalid argument count");
    uuid_copy(params.uuid_user, client->user_ptr->uuid);
    uuid_copy(params.uuid_team, client->selector.team);
    uuid_copy(params.uuid_channel, client->selector.channel);
    err =
    create_thread(&srv->database, request->args[0], request->args[1], &params);
    body = body_maker_thread(
        get_thread(&srv->database, &params), false, LOG_T_EVT_THREAD);
    if (!body)
        return EXIT_FAILURE;
    return reply(err, request, body);
}

static int create_reply_manage(server_t *srv,
request_t *request, client_t *client)
{
    void *body = NULL;
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
    body = body_maker_reply(
        get_reply(&srv->database, &params), false, LOG_T_EVT_REPLY);
    if (!body)
        return EXIT_FAILURE;
    return reply(err, request, body);
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
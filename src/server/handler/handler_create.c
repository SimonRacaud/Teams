/*
** EPITECH PROJECT, 2021
** handler_create.c
** File description:
** handler_create function
*/

#include "database.h"
#include "server.h"
#include "utility.h"
#include "request_handler_t.h"

static int create_team_manage(
    server_t *srv, request_t *request, client_t *client)
{
    void *body = NULL;
    uuid_selector_t params = {0};
    int err = SUCCESS;

    if (walen(request->args) != 2)
        return reply_str(srv, ERROR, request, "Invalid argument count");
    uuid_copy(params.uuid_user, client->user_ptr->uuid);
    err = create_team(
        &srv->database, request->args[0], request->args[1], &params);
    if (err == SUCCESS) {
        body = body_maker_team(
            get_team(&srv->database, &params), false, LOG_T_EVT_TEAM);
        reply_to_all(srv, request, body);
    }
    body = body_maker_team(
        get_team(&srv->database, &params), false, LOG_T_PRT_TEAM);
    return reply((rerr_t){err, &params}, request, body, srv);
}

static int create_channel_manage(
    server_t *srv, request_t *request, client_t *client)
{
    void *body = NULL;
    uuid_selector_t params = {0};
    int err = SUCCESS;

    if (walen(request->args) != 2)
        return reply_str(srv, ERROR, request, "Invalid argument count");
    uuid_copy(params.uuid_user, client->user_ptr->uuid);
    uuid_copy(params.uuid_team, client->selector.team);
    err = create_channel(
        &srv->database, request->args[0], request->args[1], &params);
    if (err == SUCCESS) {
        body = body_maker_channel(
            get_channel(&srv->database, &params), false, LOG_T_EVT_CHAN);
        reply_to_members(srv, request, body, params.uuid_team);
    }
    body = body_maker_channel(
        get_channel(&srv->database, &params), false, LOG_T_PRT_CHAN);
    return reply((rerr_t){err, &params}, request, body, srv);
}

static int create_thread_manage(
    server_t *srv, request_t *request, client_t *client)
{
    void *body = NULL;
    uuid_selector_t params = {0};
    int err = SUCCESS;
    thread_t *thread;

    if (walen(request->args) != 2)
        return reply_str(srv, ERROR, request, "Invalid argument count");
    uuid_copy(params.uuid_user, client->user_ptr->uuid);
    uuid_copy(params.uuid_team, client->selector.team);
    uuid_copy(params.uuid_channel, client->selector.channel);
    err = create_thread(
        &srv->database, request->args[0], request->args[1], &params);
    if (!(thread = get_thread(&srv->database, &params)))
        return EXIT_SUCCESS;
    if (err == SUCCESS) {
        body = body_maker_thread(thread, false, LOG_T_EVT_THREAD);
        reply_to_members(srv, request, body, params.uuid_team);
    }
    body = body_maker_thread(thread, false, LOG_T_PRT_THREAD);
    return reply((rerr_t){err, &params}, request, body, srv);
}

static int create_reply_manage(
    server_t *srv, request_t *request, client_t *client)
{
    void *body = NULL;
    uuid_selector_t params = {0};
    int err = SUCCESS;
    reply_t *ptr;

    if (walen(request->args) != 1)
        return reply_str(srv, ERROR, request, "Invalid argument count");
    uuid_copy(params.uuid_user, client->user_ptr->uuid);
    uuid_copy(params.uuid_team, client->selector.team);
    uuid_copy(params.uuid_channel, client->selector.channel);
    uuid_copy(params.uuid_thread, client->selector.thread);
    err = create_reply(
        &srv->database, client->user_ptr, request->args[0], &params);
    if (!(ptr = get_reply(&srv->database, &params)))
        return EXIT_SUCCESS;
    body = body_maker_reply_event(ptr, params.uuid_team);
    if (err == SUCCESS)
        reply_to_members(srv, request, body, params.uuid_team);
    body = body_maker_reply(ptr, false, LOG_T_PRT_REPLY);
    return reply((rerr_t){err, &params}, request, body, srv);
}

int handler_create(server_t *srv, request_t *request, client_t *client)
{
    if (!uuid_is_null(client->selector.thread)) {
        if (!is_subscribed(client, client->selector.team))
            return reply_error(srv, ERR_UNAUTHORISED, request, NULL);
        return create_reply_manage(srv, request, client);
    }
    if (!uuid_is_null(client->selector.channel)) {
        if (!is_subscribed(client, client->selector.team))
            return reply_error(srv, ERR_UNAUTHORISED, request, NULL);
        return create_thread_manage(srv, request, client);
    }
    if (!uuid_is_null(client->selector.team)) {
        if (!is_subscribed(client, client->selector.team))
            return reply_error(srv, ERR_UNAUTHORISED, request, NULL);
        return create_channel_manage(srv, request, client);
    }
    return create_team_manage(srv, request, client);
}
/*
** EPITECH PROJECT, 2021
** handler_info.c
** File description:
** handler_info function
*/

#include "server.h"
#include "utility.h"
#include "database.h"
#include "request_handler_t.h"

static int info_thread_manage(
    server_t *srv, request_t *request, client_t *client)
{
    uuid_selector_t params = {0};
    thread_t *thread = NULL;
    void *body = NULL;

    uuid_copy(params.uuid_user, client->user_ptr->uuid);
    uuid_copy(params.uuid_team, client->selector.team);
    uuid_copy(params.uuid_channel, client->selector.channel);
    uuid_copy(params.uuid_thread, client->selector.thread);
    thread = get_thread(&srv->database, &params);
    if (!thread)
        return reply_error(ERR_UNKNOWN_THREAD, request, params.uuid_thread);
    body = body_maker_thread(thread, false, LOG_T_PRT_THREAD);
    return reply(SUCCESS, request, body, NULL);
}

static int info_channel_manage(
    server_t *srv, request_t *request, client_t *client)
{
    uuid_selector_t params = {0};
    channel_t *channel = NULL;
    void *body = NULL;

    uuid_copy(params.uuid_user, client->user_ptr->uuid);
    uuid_copy(params.uuid_team, client->selector.team);
    uuid_copy(params.uuid_channel, client->selector.channel);
    channel = get_channel(&srv->database, &params);
    if (!channel)
        return reply_error(ERR_UNKNOWN_CHANNEL, request, params.uuid_channel);
    body = body_maker_channel(channel, false, LOG_T_PRT_CHAN);
    return reply(SUCCESS, request, body, NULL);
}

static int info_team_manage(
    server_t *srv, request_t *request, client_t *client)
{
    uuid_selector_t params = {0};
    team_t *team = NULL;
    void *body = NULL;

    uuid_copy(params.uuid_user, client->user_ptr->uuid);
    uuid_copy(params.uuid_team, client->selector.team);
    team = get_team(&srv->database, &params);
    if (!team)
        return reply_error(ERR_UNKNOWN_TEAM, request, params.uuid_team);
    body = body_maker_team(team, false, LOG_T_PRT_TEAM);
    return reply(SUCCESS, request, body, NULL);
}

static int info_user_manage(
    UNUSED server_t *srv, request_t *request, client_t *client)
{
    void *body = body_maker_user(client->user_ptr, false, LOG_T_PRT_USER);

    return reply(SUCCESS, request, body, NULL);
}

int handler_info(server_t *srv, request_t *request, client_t *client)
{
    if (!uuid_is_null(client->selector.thread))
        return info_thread_manage(srv, request, client);
    if (!uuid_is_null(client->selector.channel))
        return info_channel_manage(srv, request, client);
    if (!uuid_is_null(client->selector.team))
        return info_team_manage(srv, request, client);
    return info_user_manage(srv, request, client);
}
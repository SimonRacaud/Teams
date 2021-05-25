/*
** EPITECH PROJECT, 2021
** handler_list.c
** File description:
** handler_list function
*/

#include "database.h"
#include "server.h"
#include "utility.h"
#include "request_handler_t.h"

static int list_reply_manage(
    server_t *srv, request_t *request, client_t *client)
{
    void *body = NULL;
    uuid_selector_t params = {0};
    thread_t *thread = NULL;

    uuid_copy(params.uuid_user, client->user_ptr->uuid);
    uuid_copy(params.uuid_team, client->selector.team);
    uuid_copy(params.uuid_channel, client->selector.channel);
    uuid_copy(params.uuid_thread, client->selector.thread);
    thread = get_thread(&srv->database, &params);
    if (!thread)
        return reply_error(
            srv, ERR_UNKNOWN_THREAD, request, &params.uuid_thread);
    body = body_maker_reply(thread->replies.lh_first, true, LOG_T_PRT_REPLY);
    return reply((rerr_t){SUCCESS, NULL}, request, body, srv);
}

static int list_thread_manage(
    server_t *srv, request_t *request, client_t *client)
{
    void *body = NULL;
    uuid_selector_t params = {0};
    channel_t *channel = NULL;

    uuid_copy(params.uuid_user, client->user_ptr->uuid);
    uuid_copy(params.uuid_team, client->selector.team);
    uuid_copy(params.uuid_channel, client->selector.channel);
    channel = get_channel(&srv->database, &params);
    if (!channel)
        return reply_error(
            srv, ERR_UNKNOWN_CHANNEL, request, &params.uuid_channel);
    body = body_maker_thread(channel->threads.lh_first, true, LOG_T_PRT_THREAD);
    return reply((rerr_t){SUCCESS, NULL}, request, body, srv);
}

static int list_channel_manage(
    server_t *srv, request_t *request, client_t *client)
{
    void *body = NULL;
    uuid_selector_t params = {0};
    team_t *team = NULL;

    uuid_copy(params.uuid_user, client->user_ptr->uuid);
    uuid_copy(params.uuid_team, client->selector.team);
    team = get_team(&srv->database, &params);
    if (!team)
        return reply_error(srv, ERR_UNKNOWN_TEAM, request, &params.uuid_team);
    body = body_maker_channel(team->channels.lh_first, true, LOG_T_PRT_CHAN);
    return reply((rerr_t){SUCCESS, NULL}, request, body, srv);
}

static int list_team_manage(
    server_t *srv, request_t *request, UNUSED client_t *client)
{
    void *body =
        body_maker_team(srv->database.teams.lh_first, true, LOG_T_PRT_TEAM);

    return reply((rerr_t){SUCCESS, NULL}, request, body, srv);
}

int handler_list(server_t *srv, request_t *request, client_t *client)
{
    if (!uuid_is_null(client->selector.thread))
        return list_reply_manage(srv, request, client);
    if (!uuid_is_null(client->selector.channel))
        return list_thread_manage(srv, request, client);
    if (!uuid_is_null(client->selector.team))
        return list_channel_manage(srv, request, client);
    return list_team_manage(srv, request, client);
}
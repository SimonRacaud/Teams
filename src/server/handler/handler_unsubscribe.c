/*
** EPITECH PROJECT, 2021
** handler_unsubscribe.c
** File description:
** handler_unsubscribe function
*/

#include "database.h"
#include "server.h"
#include "utility.h"
#include "request_handler_t.h"

static void event(team_t *team, user_t *user)
{
    char team_uuid[UUID_STR];
    char user_uuid[UUID_STR];

    uuid_unparse(team->uuid, team_uuid);
    uuid_unparse(user->uuid, user_uuid);
    server_event_user_unsubscribed(team_uuid, user_uuid);
}

static bool remove_from_user(team_t *team, uuid_t user_uuid)
{
    user_t *node = NULL;

    LIST_FOREACH(node, &team->users, entries)
    {
        if (!uuid_compare(node->uuid, user_uuid)) {
            LIST_REMOVE(node, entries);
            return true;
        }
    }
    return false;
}

static int unsubscribe_manage(
    request_t *request, client_t *client, uuid_selector_t *selector, server_t *srv)
{
    void *body = NULL;
    bool ret_val = false;
    team_t *node = NULL;

    LIST_FOREACH(node, &client->user_ptr->teams, entries) {
        if (!uuid_compare(node->uuid, selector->uuid_team)) {
            ret_val = remove_from_user(node, client->user_ptr->uuid);
            LIST_REMOVE(node, entries);
            break;
        }
    }
    if (!ret_val)
        return reply_error(srv, ERR_UNKNOWN_TEAM, request, &selector->uuid_team);
    body = body_maker_subscription(client->user_ptr->uuid, node->uuid);
    if (!body)
        return EXIT_FAILURE;
    event(node, client->user_ptr);
    return reply((rerr_t){SUCCESS, NULL}, request, body, srv);
}

int handler_unsubscribe(server_t *srv, request_t *request, client_t *client)
{
    uuid_selector_t selector = {0};

    if (walen(request->args) != 1)
        return reply_str(srv, ERROR, request, "Invalid argument count");
    if (uuid_parse(request->args[0], selector.uuid_team) == -1)
        return reply_error(srv, ERR_UNKNOWN_TEAM, request, NULL);
    uuid_copy(selector.uuid_user, client->user_ptr->uuid);
    return unsubscribe_manage(request, client, &selector, srv);
}
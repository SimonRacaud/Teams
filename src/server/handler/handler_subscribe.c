/*
** EPITECH PROJECT, 2021
** handler_subscribe.c
** File description:
** handler_subscribe function
*/

#include "server.h"
#include "utility.h"
#include "database.h"
#include "request_handler_t.h"

static void event(team_t *team, user_t *user)
{
    char team_uuid[UUID_STR];
    char user_uuid[UUID_STR];

    uuid_unparse(team->uuid, team_uuid);
    uuid_unparse(user->uuid, user_uuid);
    server_event_user_subscribed(team_uuid, user_uuid);
}

static int subscribe_manage(server_t *srv, request_t *request, client_t *client,
    uuid_selector_t *selector)
{
    team_t *team = get_team(&srv->database, selector);
    user_ptr_t *user_ptr = malloc(sizeof(user_ptr_t));
    team_ptr_t *team_ptr = malloc(sizeof(team_ptr_t));
    void *body = NULL;

    if (!team || !user_ptr || !team_ptr)
        return reply_error(
            srv, ERR_UNKNOWN_TEAM, request, &selector->uuid_team);
    user_ptr->ptr = client->user_ptr;
    team_ptr->ptr = team;
    LIST_INSERT_HEAD(&client->user_ptr->teams, team_ptr, entries);
    LIST_INSERT_HEAD(&team->users, user_ptr, entries);
    body = body_maker_subscription(client->user_ptr->uuid, team->uuid);
    if (!body)
        return EXIT_FAILURE;
    event(team, client->user_ptr);
    return reply((rerr_t){SUCCESS, NULL}, request, body, srv);
}

int handler_subscribe(server_t *srv, request_t *request, client_t *client)
{
    uuid_selector_t selector = {0};

    if (walen(request->args) != 1)
        return reply_str(srv, ERROR, request, "Invalid argument count");
    if (uuid_parse(request->args[0], selector.uuid_team) == -1)
        return reply_error(srv, ERR_UNKNOWN_TEAM, request, NULL);
    uuid_copy(selector.uuid_user, client->user_ptr->uuid);
    return subscribe_manage(srv, request, client, &selector);
}
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

static int subscribe_manage(server_t *srv, request_t *request, client_t *client,
    uuid_selector_t *selector)
{
    team_t *team = get_team(&srv->database, selector);

    if (!team)
        return reply_str(ERR_UNKNOWN_TEAM, request, "Bad argument value");
    LIST_INSERT_HEAD(&client->user_ptr->teams, team, entries);
    LIST_INSERT_HEAD(&team->users, client->user_ptr, entries);
    return reply_str(SUCCESS, request, "Correctly subscribe");
}

int handler_subscribe(server_t *srv, request_t *request, client_t *client)
{
    uuid_selector_t selector = {0};

    if (walen(request->args) != 1)
        return reply_str(ERROR, request, "Invalid argument count");
    if (uuid_parse(request->args[0], selector.uuid_team) == -1)
        return reply_str(ERROR, request, "Bad argument value");
    uuid_copy(selector.uuid_user, client->user_ptr->uuid);
    return subscribe_manage(srv, request, client, &selector);
}
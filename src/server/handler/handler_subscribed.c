/*
** EPITECH PROJECT, 2021
** handler_subscribed.c
** File description:
** handler_subscribed function
*/

#include "server.h"
#include "utility.h"
#include "database.h"
#include "request_handler_t.h"

static int parametting_manage(server_t *srv, request_t *request, uuid_selector_t *params)
{
    void *body = NULL;
    team_t *team = get_team(&srv->database, params);

    if (!team)
        return EXIT_FAILURE;
    body = body_maker_user(team->users.lh_first, true);
    if (!body)
        return EXIT_FAILURE;
    return reply(SUCCESS, request, body);
}

static int noparametting_manage(request_t *request, client_t *client)
{
    void *body = NULL;

    if (LIST_EMPTY(&client->user_ptr->teams))
        return reply_str(ERROR, request, "No team subscribed");
    body = body_maker_team(client->user_ptr->teams.lh_first, true);
    if (!body)
        return EXIT_FAILURE;
    return reply(SUCCESS, request, body);
}

int handler_subscribed(server_t *srv, request_t *request, client_t *client)
{
    uuid_selector_t selector = {0};
    size_t size = walen(request->args);

    if (size == 1) {
        if (uuid_parse(request->args[0], selector.uuid_team) == -1)
            return reply_str(ERROR, request, "Bad argument value");
        uuid_copy(selector.uuid_user, client->user_ptr->uuid);
        return parametting_manage(srv, request, &selector);
    } else if (size == 0) {
        return noparametting_manage(request, client);
    }
    return reply_str(ERROR, request, "Invalid argument count");
}
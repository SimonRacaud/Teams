/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 17/05/2021 logout.c
*/

#include "env.h"
#include "server.h"
#include "utility.h"
#include "logging_server.h"

static int do_logout(request_t *request, client_t *client, server_t *srv)
{
    char uuid[UUID_STR];
    user_t *user = client->user_ptr;
    void *body;

    uuid_unparse(user->uuid, uuid);
    server_event_user_logged_out(uuid);
    client->user_ptr->status = DISCONNECTED;
    client->user_ptr = NULL;
    body = body_maker_user(user, false, LOG_T_LOGGING);
    return reply_to_all(srv, request, body);
}

int handler_logout(
    UNUSED server_t *server, request_t *request, client_t *client)
{
    if (walen(request->args) != 0) {
        return reply_str(server, ERROR, request, "Bad argument count");
    }
    if (client->user_ptr == NULL) {
        return reply_error(server, ERR_UNAUTHORISED, request, NULL);
    } else {
        return do_logout(request, client, server);
    }
}
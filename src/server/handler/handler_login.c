/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 17/05/2021 login.c
*/

#include "database.h"
#include "server.h"
#include "utility.h"
#include "logging_server.h"

static int do_login(server_t *server, request_t *request, client_t *client,
    uuid_selector_t *selector)
{
    user_t *user = get_user(&server->database, selector);
    char uuid[UUID_STR];
    void *res_body;

    if (!user)
        return EXIT_FAILURE;
    client->user_ptr = user;
    res_body = body_maker_user(user, false);
    if (!res_body)
        return EXIT_FAILURE;
    uuid_unparse(user->uuid, uuid);
    server_event_user_logged_in(uuid);
    return reply(SUCCESS, request, res_body);
}

int handler_login(server_t *server, request_t *request, client_t *client)
{
    uuid_selector_t selector = {0};
    char *username;
    rcode_e code;

    if (walen(request->args) != 1) {
        return reply_str(ERROR, request, "Bad argument count");
    }
    username = request->args[0];
    if (is_empty(username)) {
        return reply_str(ERROR, request, "Bad argument value");
    }
    code = create_user(&server->database, username, &selector);
    if (code == SUCCESS || code == ERR_ALREADY_EXIST) {
        return do_login(server, request, client, &selector);
    } else {
        printf("login: fail to create user\n");
        return reply_str(code, request, "Fail to create user");
    }
}
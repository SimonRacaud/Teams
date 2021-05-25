/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 12/05/2021 request_execute.c
*/

#include "server.h"
#include "request_handler_t.h"

const request_handler_t HANDLERS[] = {
    {.label = "help", .handler = handler_help, .connection = false},
    {.label = "login", .handler = &handler_login, .connection = false},
    {.label = "logout", .handler = &handler_logout, .connection = false},
    {.label = "users", .handler = handler_users, .connection = true},
    {.label = "user", .handler = handler_user, .connection = true},
    {.label = "send", .handler = handler_send, .connection = true},
    {.label = "messages", .handler = handler_messages, .connection = true},
    {.label = "subscribe", .handler = handler_subscribe, .connection = true},
    {.label = "subscribed", .handler = handler_subscribed, .connection = true},
    {.label = "use", .handler = handler_use, .connection = true},
    {.label = "create", .handler = handler_create, .connection = true},
    {.label = "list", .handler = handler_list, .connection = true},
    {.label = "info", .handler = handler_info, .connection = true},
    {.label = "unsubscribe",
    .handler = handler_unsubscribe, .connection = true},
    {.label = NULL, .handler = NULL, .connection = false}};

static int call_handler(
    request_t *request, server_t *server, handler_t handler, client_t *client)
{
    if (handler) {
        if (handler(server, request, client) == EXIT_FAILURE) {
            printf("An error occurred during the command execution\n");
        }
    }
    return EXIT_SUCCESS;
}

int request_execute(request_t *request, server_t *server, client_t *client)
{
    int cmp = 0;

    request->receiver = &client->socket;
    for (size_t i = 0; HANDLERS[i].label != NULL; i++) {
        cmp = strcmp(HANDLERS[i].label, request->label);
        if (cmp == 0 && (!HANDLERS[i].connection || client->user_ptr)) {
            return call_handler(request, server, HANDLERS[i].handler, client);
        } else if (cmp == 0) {
            return reply_error(server, ERR_UNAUTHORISED, request, NULL);
        }
    }
    if (reply_str(server, ERROR, request, "Command not found") == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
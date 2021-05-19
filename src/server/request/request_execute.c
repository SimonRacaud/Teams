/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 12/05/2021 request_execute.c
*/

#include "server.h"
#include "request_handler_t.h"

const request_handler_t HANDLERS[] = {
    {.label = "help", .handler = handler_help},
    {.label = "login", .handler = &handler_login},
    {.label = "logout", .handler = &handler_logout},
    {.label = "users", .handler = handler_users},
    {.label = "user", .handler = handler_user},
    {.label = "send", .handler = handler_send},
    {.label = "messages", .handler = handler_messages},
    {.label = "subscribe", .handler = NULL},
    {.label = "subscribed", .handler = NULL},
    {.label = "unsubscribe", .handler = NULL},
    {.label = "use", .handler = NULL},
    {.label = "create", .handler = NULL},
    {.label = "list", .handler = NULL},
    {.label = "info", .handler = NULL},
    {.label = NULL, .handler = NULL}};

static int call_handler(
    request_t *request, server_t *server, handler_t handler, client_t *client)
{
    if (handler) {
        return handler(server, request, client);
    }
    return EXIT_SUCCESS;
}

int request_execute(request_t *request, server_t *server, client_t *client)
{
    request->receiver = &client->socket;
    for (size_t i = 0; HANDLERS[i].label != NULL; i++) {
        if (strcmp(HANDLERS[i].label, request->label) == 0) {
            return call_handler(request, server, HANDLERS[i].handler, client);
        }
    }
    if (reply_str(ERROR, request, "Command not found") == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
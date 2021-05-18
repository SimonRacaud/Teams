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
    {.label = "login", .handler = NULL},
    {.label = "logout", .handler = NULL},
    {.label = "users", .handler = handler_users},
    {.label = "user", .handler = handler_user},
    {.label = "send", .handler = NULL},
    {.label = "messages", .handler = NULL},
    {.label = "subscribe", .handler = NULL},
    {.label = "subscribed", .handler = NULL},
    {.label = "unsubscribe", .handler = NULL},
    {.label = "use", .handler = NULL},
    {.label = "create", .handler = NULL},
    {.label = "list", .handler = NULL},
    {.label = "info", .handler = NULL},
    {.label = NULL, .handler = NULL}};

static int call_handler(
    request_t *request, server_t *server, handler_t handler)
{
    if (handler) {
        return handler(server, request);
    }
    return EXIT_SUCCESS;
}

static void command_not_found(request_t *request, client_t *client)
{
    response_t *response = NULL;

    response = response_create(ERROR, request, &client->socket, NULL);
    printf("WARNING: command not found.\n");
    if (!response) {
        return;
    }
    response_send(response);
    response_destroy(response);
}

int request_execute(request_t *request, server_t *server, client_t *client)
{
    request->receiver = &client->socket;
    for (size_t i = 0; HANDLERS[i].label != NULL; i++) {
        if (strcmp(HANDLERS[i].label, request->label) == 0) {
            return call_handler(request, server, HANDLERS[i].handler);
        }
    }
    command_not_found(request, client);
    return EXIT_SUCCESS;
}
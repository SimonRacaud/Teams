/*
** EPITECH PROJECT, 2021
** handler_use.c
** File description:
** handler_use function
*/

#include "server.h"
#include "utility.h"
#include "database.h"
#include "request_handler_t.h"

int handler_use(server_t *srv, request_t *request, client_t *client)
{
    (void) srv;
    (void) request;
    (void) client;
    return reply_str(ERROR, request, "Not already dev");
}
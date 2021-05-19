/*
** EPITECH PROJECT, 2021
** handler_create.c
** File description:
** handler_create function
*/

#include "server.h"
#include "utility.h"
#include "database.h"
#include "request_handler_t.h"

int handler_create(server_t *srv, request_t *req, UNUSED client_t *client)
{
    (void) srv;
    (void) req;
    return reply_str(ERROR, req, "Not already dev");
}
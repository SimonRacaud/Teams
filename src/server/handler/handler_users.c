/*
** EPITECH PROJECT, 2021
** handler_users.c
** File description:
** handler_users function
*/

#include "server.h"

int handler_users(server_t *srv, request_t *request, UNUSED client_t *client)
{
    void *body;

    body = body_maker_user(
        LIST_FIRST(&srv->database.users), true, LOG_T_PRT_USER);
    return reply(SUCCESS, request, body, NULL);
}
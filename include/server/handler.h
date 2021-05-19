/*
** EPITECH PROJECT, 2021
** handler.h
** File description:
** handler
*/

#ifndef HANDLER_H
#define HANDLER_H

#include "server.h"

#ifndef UNUSED
#define UNUSED __attribute__((unused))
#endif

/* For messages command */
typedef struct mp_list_s mp_list_t;
LIST_HEAD(mp_list_s, private_msg_s);

/*
**
** HANDLER TOOLS
**
*/

size_t get_arg_size(const char **arg);
void get_uuid_from_string(uuid_t dest, const char *str);

/*
**
** HANDLER
**
*/

int handler_send(server_t *srv, request_t *request, client_t *client);
int handler_help(server_t *srv, request_t *request, client_t *client);
int handler_user(server_t *srv, request_t *request, client_t *client);
int handler_users(server_t *srv, request_t *request, client_t *client);
int handler_logout(server_t *server, request_t *request, client_t *client);
int handler_login(server_t *server, request_t *request, client_t *client);
int handler_messages(
    server_t *server, request_t *request, UNUSED client_t *client);

#endif
/*
** EPITECH PROJECT, 2021
** handler.h
** File description:
** handler
*/

#ifndef HANDLER_H
#define HANDLER_H

#include "server.h"

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

int handler_help(server_t *srv, request_t *request, client_t *client);
int handler_user(server_t *srv, request_t *request, client_t *client);
int handler_users(server_t *srv, request_t *request, client_t *client);
int handler_logout(server_t *server, request_t *request, client_t *client);
int handler_login(server_t *server, request_t *request, client_t *client);

#endif
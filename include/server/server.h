/*
** EPITECH PROJECT, 2021
** My TEAMS
** File description:
** app
*/

#ifndef APP_H_
#define APP_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/queue.h>
#include "server_t.h"
#include "socket.h"
#include "network.h"
#include "handler.h"

#define SERVER_MAX_CLIENT 42

#define MY_LIST_INIT(head) head.lh_first = NULL

#define FD_READ_ISSET(el, server) \
    FD_ISSET(el->socket.fd, &server->select.read_fds)
#define FD_WRITE_ISSET(el, server) \
    FD_ISSET(el->receiver->fd, &server->select.write_fds)

///     APP
int app_create(server_t *server, uint port);
int app_loop(server_t *server);
int app_destroy(server_t *server);

int app_select(server_t *server);

int process_request(server_t *server, client_t *client);
int request_execute(request_t *request, server_t *server, client_t *client);

/// CLIENT
int connect_client(server_t *server);
void disconnect_client(client_t *client);

#endif /* !APP_H_ */

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

#include "socket.h"
#include "client_t.h"
#include "utility.h"
#include "network.h"
#include "network/response_t.h"

#define CONNECT_ATTEMPT 10
#define MY_LIST_HEAD_INITIALIZER(head) head.slh_first = NULL

/// INIT
int app_init(client_t *client, int argc, char **argv);
int connect_to_server(client_t *client, uint port, const char *ip);
int parse_args(args_t *args, int argc, char **argv);

/// DESTROY
int app_destroy(client_t *client);

/// LOOP
int app_loop(client_t *client);
int process_write(client_t *client);
int process_read(client_t *client);
char *prompt(buffer_t *buffer, bool *disconnect);

#endif /* !APP_H_ */

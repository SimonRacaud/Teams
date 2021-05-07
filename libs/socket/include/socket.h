/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myftp-simon.racaud
** File description:
** 15/04/2021 socket.h
*/

#ifndef SOCKET_H
#define SOCKET_H

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <netdb.h>

#include "socket_t.h"
#include "select_t.h"

#define RANDOM_PORT 0

/// Uncomment to activate debug mode
/// #define DEBUG 1

#define TO_PROCESS(connection, fds) FD_ISSET(connection->sock.fd, &fds)

int socket_server_create(socket_t *sock, uint port, uint max_client);

int fd_select(select_t *data, size_t size_read, size_t size_write, ...);
int socket_server_connect(socket_t *client, int server_fd);

char *fd_getline(int fd, char **buffer_ptr, bool *empty);
int socket_send(socket_t *sock, const char *msg);

int socket_client_ip_connect(socket_t *sock, uint port, const char *ip);
int socket_client_hostname_connect(
    socket_t *sock, uint port, const char *hostname);

int socket_close(socket_t *sock);

// DEBUG
void debug_socket(socket_t *sock, const char *msg);

#endif // SOCKET_H

/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myftp-simon.racaud
** File description:
** 15/04/2021 socket_server_create.c
*/

#include "socket.h"

static void debug(__attribute__((unused))const uint port)
{
    #ifdef DEBUG
    fprintf(stderr, "Server is listening on port %u.\n", port);
    #endif
}

static int socket_bind(socket_t *sock, uint port)
{
    sock->conf.sin_addr.s_addr = htonl(INADDR_ANY);
    sock->conf.sin_port = htons(port);
    sock->conf.sin_family = AF_INET;
    if (bind(
        sock->fd, (struct sockaddr *) &sock->conf, sizeof(struct sockaddr))
        == -1) {
        perror("bind()");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int socket_server_create(socket_t *sock, uint port, uint max_client)
{
    int opt = 1;

    sock->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock->fd == -1) {
        perror("socket");
        return EXIT_FAILURE;
    }
    if (setsockopt(sock->fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
            sizeof(opt))) {
        perror("setsockopt");
        return EXIT_FAILURE;
    }
    if (socket_bind(sock, port) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (listen(sock->fd, max_client) == -1) {
        perror("listen()");
        return EXIT_FAILURE;
    }
    debug(port);
    return EXIT_SUCCESS;
}
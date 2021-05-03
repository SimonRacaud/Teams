/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myftp-simon.racaud
** File description:
** 15/04/2021 socket_client_connect.c
*/

#include "socket.h"

int socket_client_ip_connect(socket_t *sock, uint port, const char *ip)
{
    sock->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock->fd == -1) {
        perror("socket");
        return EXIT_FAILURE;
    }
    sock->conf.sin_family = AF_INET;
    sock->conf.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &sock->conf.sin_addr) <= 0) {
        return EXIT_FAILURE;
    }
    if (connect(sock->fd, (struct sockaddr *) &sock->conf, sizeof(sock->conf))
        == -1) {
        perror("connect");
        return EXIT_FAILURE;
    }
    #ifdef DEBUG
    debug_socket(sock, "Client connected");
    #endif
    return EXIT_SUCCESS;
}
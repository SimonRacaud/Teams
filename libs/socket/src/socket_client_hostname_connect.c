/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myftp-simon.racaud
** File description:
** 15/04/2021 socket_client_connect.c
*/

#include "socket.h"

static int connect_to_server(
    socket_t *sock, uint port, struct hostent *hostinfo)
{
    sock->conf.sin_family = AF_INET;
    sock->conf.sin_port = htons(port);
    sock->conf.sin_addr = *(struct in_addr *) hostinfo->h_addr;
    if (connect(sock->fd, (struct sockaddr *) &sock->conf, sizeof(sock->conf))
        == -1) {
        perror("connect");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int socket_client_hostname_connect(
    socket_t *sock, uint port, const char *hostname)
{
    struct hostent *hostinfo = gethostbyname(hostname);

    if (hostinfo == NULL) {
        perror("gethostbyname");
        return EXIT_FAILURE;
    }
    sock->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock->fd == -1) {
        perror("socket");
        return EXIT_FAILURE;
    }
    if (connect_to_server(sock, port, hostinfo) == EXIT_FAILURE)
        return EXIT_FAILURE;
#ifdef DEBUG
    debug_socket(sock, "Client connected");
#endif
    return EXIT_SUCCESS;
}
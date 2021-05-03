/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myftp-simon.racaud
** File description:
** 15/04/2021 socker_send.c
*/

#include "socket.h"

int socket_send(socket_t *sock, const char *msg)
{
    size_t len = strlen(msg);

    if (write(sock->fd, msg, len) == -1) {
        perror("write");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myftp-simon.racaud
** File description:
** 15/04/2021 socket_close.c
*/

#include "socket.h"

int socket_close(socket_t *sock)
{
    #ifdef DEBUG
    debug_socket(sock, "Disconnected");
    #endif
    if (close(sock->fd) == -1) {
        perror("close");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
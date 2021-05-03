/*
** EPITECH PROJECT, 2021
** HUB_my_troyan
** File description:
** 01/05/2021 debug_socket.c
*/

#include "socket.h"

void debug_socket(socket_t *sock, const char *msg)
{
    char ip[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &(sock->conf.sin_addr), ip, INET_ADDRSTRLEN);
    fprintf(stderr, "%s: ip(%s), port(%u)\n", msg, ip, sock->conf.sin_port);
}

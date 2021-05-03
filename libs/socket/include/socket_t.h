/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myftp-simon.racaud
** File description:
** 15/04/2021 socket_t.h
*/

#ifndef SOCKET_T_H
#define SOCKET_T_H

#include <netinet/in.h>

typedef struct socket {
    int fd;
    struct sockaddr_in conf;
} socket_t;

#endif // SOCKET_T_H

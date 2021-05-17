/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 connection_to_server.c
*/

#include "client.h"

int connect_to_server(socket_t *sock, uint port, const char *ip)
{
    for (size_t attempt = 0; attempt < CONNECT_ATTEMPT; attempt++) {
        if (socket_client_ip_connect(sock, port, ip) == EXIT_SUCCESS) {
            return EXIT_SUCCESS;
        }
        sleep(1);
    }
    printf("Too many attempt. quit\n");
    return EXIT_FAILURE;
}
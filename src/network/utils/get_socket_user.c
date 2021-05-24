/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 21/05/2021 get_socket_user.c
*/

#include "server.h"

socket_t *get_socket_user(server_t *server, user_t *user)
{
    client_t *ptr = NULL;

    LIST_FOREACH(ptr, &server->clients, entries) {
        if (ptr->user_ptr == user) {
            return &ptr->socket;
        }
    }
    return NULL;
}
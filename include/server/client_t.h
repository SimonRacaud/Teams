/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 client_t.h
*/

#ifndef CLIENT_T_H
#define CLIENT_T_H

#include "data/user_t.h"
#include "socket_t.h"

typedef struct client_list_header client_list_t;

typedef struct client_s {
    user_t *user_ptr;
    char *read_buffer;
    socket_t socket;
    LIST_ENTRY(client_s) entries;
} client_t;

#endif // CLIENT_T_H

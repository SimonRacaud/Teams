/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 client_t.h
*/

#ifndef CLIENT_T_H
#define CLIENT_T_H

#include "client/selected_entity_t.h"
#include "data/user_t.h"
#include "socket_t.h"
#include "socket.h"

typedef struct client_list_header client_list_t;

typedef struct client_s {
    user_t *user_ptr;
    buffer_t buffer;
    socket_t socket;
    selected_entity_t selector;
    LIST_ENTRY(client_s) entries;
} client_t;

#endif // CLIENT_T_H

/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 client_t.h
*/

#ifndef CLIENT_T_H
#define CLIENT_T_H

#include "socket_t.h"
#include "select_t.h"
#include "selected_entity_t.h"
#include "args_t.h"
#include <sys/queue.h>
#include "network/request_t.h"

typedef struct request_stack_s request_stack_t;

typedef struct client_s {
    args_t args;
    selected_entity_t selector;
    select_t select;
    socket_t socket;
    bool loop;
    char *cli_buffer;
    SLIST_HEAD(request_stack_s, request_s) stack;
} client_t;

#endif // CLIENT_T_H

/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 server_t.h
*/

#ifndef SERVER_T_H
#define SERVER_T_H

#include "data/database_t.h"
#include "select_t.h"
#include "socket_t.h"
#include "client_t.h"
#include <sys/queue.h>
#include "network/response_t.h"

typedef struct response_stack response_stack_t;

typedef struct server_s {
    database_t database;
    select_t select;
    socket_t socket;
    bool loop;
    LIST_HEAD(client_list_header, client_s) clients;
    SLIST_HEAD(response_stack, response_s) responses;
} server_t;

#endif // SERVER_T_H

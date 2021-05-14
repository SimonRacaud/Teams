/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 request_t.h
*/

#ifndef REQUEST_T_H
#define REQUEST_T_H

#include "socket_t.h"
#include <sys/queue.h>

typedef struct request_s {
    socket_t *receiver;
    char *label;
    char **args;
    SLIST_ENTRY(request_s) entries;
} request_t;

#endif // REQUEST_T_H

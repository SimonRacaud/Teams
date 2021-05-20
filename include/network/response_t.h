/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 response_t.h
*/

#ifndef RESPONSE_T_H
#define RESPONSE_T_H

#include "socket_t.h"
#include "env.h"
#include <sys/queue.h>

typedef enum response_error_code {
    SUCCESS = 0,
    ERROR = 1,
    ERR_UNAUTHORISED = 2,
    ERR_ALREADY_EXIST = 3,
    ERR_UNKNOWN_USER = 4,
    ERR_UNKNOWN_THREAD = 5,
    ERR_UNKNOWN_CHANNEL = 6,
    ERR_UNKNOWN_TEAM = 7
} rcode_e;

typedef struct body_header_s {
    uint elem_size;
    uint list_size;
    char entity[SIZE_NAME];
    char logger[SIZE_NAME];
} body_header_t;

typedef struct response_s {
    socket_t *receiver;
    rcode_e err_code;
    char *req_label;
    char **req_args;
    body_header_t *header;
    void *body;
    SLIST_ENTRY(response_s) entries;
} response_t;

#endif // RESPONSE_T_H

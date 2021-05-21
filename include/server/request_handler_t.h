/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 12/05/2021 request_handler_t.h
*/

#ifndef REQUEST_HANDLER_T_H
#define REQUEST_HANDLER_T_H

typedef int (* handler_t)(server_t *, request_t *, client_t *);

typedef struct request_handler_s {
    const char *label;
    handler_t handler;
    bool connection;
} request_handler_t;

#endif // REQUEST_HANDLER_T_H

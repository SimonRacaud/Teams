/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 22/05/2021 response_push.c
*/

#include "network.h"

void response_push(server_t *server, response_t *response)
{
    if (response && server) {
        SLIST_INSERT_HEAD(&server->responses, response, entries);
    }
}

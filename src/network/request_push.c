/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 12/05/2021 request_push.c
*/

#include "network/request_t.h"
#include "socket_t.h"
#include "client.h"

void request_push(request_stack_t *stack, request_t *req, socket_t *client)
{
    req->receiver = client;
    SLIST_INSERT_HEAD(stack, req, entries);
}
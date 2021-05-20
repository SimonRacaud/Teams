/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 19/05/2021 body_maker_subscription.c
*/

#include "server.h"
#include "network/response_t.h"
#include "save/bin_subscription_t.h"

static void write_content(void *body, uuid_t team, uuid_t user)
{
    bin_subscription_t *ptr = NULL;

    ptr = (bin_subscription_t *)((char *)body + sizeof(body_header_t));
    uuid_copy(ptr->user, user);
    uuid_copy(ptr->team, team);
}

void *body_maker_subscription(uuid_t user, uuid_t team)
{
    body_header_t *head;
    void *body = NULL;

    body = malloc(sizeof(body_header_t) + sizeof(bin_subscription_t));
    if (!body)
        return NULL;
    head = body;
    *head = (body_header_t) {.elem_size = sizeof(bin_subscription_t),
        .list_size = 1, .entity = "subscription", .logger = "subscription"};
    write_content(body, team, user);
    return body;
}
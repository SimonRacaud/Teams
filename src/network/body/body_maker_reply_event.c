/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 19/05/2021 body_maker_reply_event.c
*/

#include "server.h"
#include "network/response_t.h"
#include "save/bin_reply_event_t.h"

static void write_content(void *body, uuid_t team, reply_t *reply)
{
    bin_reply_event_t *ptr = NULL;

    ptr = (bin_reply_event_t *)((char *)body + sizeof(body_header_t));
    uuid_copy(ptr->team, team);
    if (reply->parent_thread == NULL)
        uuid_clear(ptr->thread);
    else
        uuid_copy(ptr->thread, reply->parent_thread->uuid);
    if (reply->user == NULL)
        uuid_clear(ptr->user);
    else
        uuid_copy(ptr->user, reply->user->uuid);
    strcpy(ptr->body, reply->body);
}

void *body_maker_reply_event(reply_t *reply, uuid_t team)
{
    body_header_t *head;
    void *body = NULL;

    body = malloc(sizeof(body_header_t) + sizeof(bin_reply_event_t));
    if (!body)
        return NULL;
    head = body;
    *head = (body_header_t) {.elem_size = sizeof(bin_reply_event_t),
        .list_size = 1, .entity = "reply_event", .logger = "event_reply"};
    write_content(body, team, reply);
    return body;
}

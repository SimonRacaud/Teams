/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 body_maker_reply.c
*/

#include "database.h"
#include "server.h"
#include "network/response_t.h"

static size_t get_list_size(reply_t *ptr, bool is_list)
{
    size_t size = 0;

    if (!is_list) {
        return 1;
    } else {
        for (reply_t *node = ptr; node; node = LIST_NEXT(node, entries))
            size++;
        return size;
    }
}

static void write_content(void *body, bool is_list, reply_t *reply)
{
    bin_reply_t *packet = NULL;
    bin_reply_t *ptr = NULL;

    ptr = (bin_reply_t *)((char *)body + sizeof(body_header_t));
    for (reply_t *node = reply; node; node = LIST_NEXT(node, entries)) {
        packet = serializer_reply_t(node);
        *ptr = *packet;
        free(packet);
        ptr++;
        if (!is_list)
            break;
    }
}

void *body_maker_reply(reply_t *reply, bool is_list, const char *logger)
{
    size_t size = get_list_size(reply, is_list);
    void *body = NULL;
    body_header_t *head;

    body = malloc(sizeof(body_header_t) + sizeof(bin_reply_t) * size);
    if (!body)
        return NULL;
    head = body;
    *head = (body_header_t){.elem_size = sizeof(bin_reply_t),
        .list_size = size, .entity = "reply", .logger = ""};
    strncpy(head->logger, logger, SIZE_NAME);
    write_content(body, is_list, reply);
    return body;
}
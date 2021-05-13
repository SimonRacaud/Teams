/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 body_maker_channel.c
*/

#include "database.h"
#include "server.h"
#include "network/response_t.h"

static size_t get_list_size(channel_t *ptr, bool is_list)
{
    size_t size = 0;

    if (!is_list) {
        return 1;
    } else {
        for (channel_t *node = ptr; node; node = LIST_NEXT(node, entries))
            size++;
        return size;
    }
}

void *body_maker_channel(channel_t *channel, bool is_list)
{
    size_t size = get_list_size(channel, is_list);
    bin_channel_t *packet = NULL;
    bin_channel_t *ptr = NULL;
    void *body = NULL;

    body = malloc(sizeof(body_header_t) + sizeof(bin_channel_t) * size);
    if (!body)
        return NULL;
    *((body_header_t *) body) =
        (body_header_t){.elem_size = sizeof(bin_channel_t),
            .list_size = size,
            .type = "channel"};
    ptr = (body + sizeof(body_header_t));
    for (channel_t *node = channel; node; node = LIST_NEXT(node, entries)) {
        packet = serializer_channel_t(node);
        *ptr = *packet;
        free(packet);
        ptr++;
    }
    return body;
}
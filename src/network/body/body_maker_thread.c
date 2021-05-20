/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 body_maker_thread.c
*/

#include "database.h"
#include "server.h"
#include "network/response_t.h"

static size_t get_list_size(thread_t *ptr, bool is_list)
{
    size_t size = 0;

    if (!is_list) {
        return 1;
    } else {
        for (thread_t *node = ptr; node; node = LIST_NEXT(node, entries))
            size++;
        return size;
    }
}

static void write_content(void *body, thread_t *thread, bool is_list)
{
    bin_thread_t *packet = NULL;
    bin_thread_t *ptr = NULL;

    ptr = (bin_thread_t *)((char *)body + sizeof(body_header_t));
    for (thread_t *node = thread; node; node = LIST_NEXT(node, entries)) {
        packet = serializer_thread_t(node);
        *ptr = *packet;
        free(packet);
        ptr++;
        if (!is_list)
            break;
    }
}

void *body_maker_thread(thread_t *thread, bool is_list)
{
    size_t size = get_list_size(thread, is_list);

    void *body = NULL;

    body = malloc(sizeof(body_header_t) + sizeof(bin_thread_t) * size);
    if (!body)
        return NULL;
    *((body_header_t *) body) =
        (body_header_t){.elem_size = sizeof(bin_thread_t),
            .list_size = size,
            .type = "thread"};
    write_content(body, thread, is_list);
    return body;
}
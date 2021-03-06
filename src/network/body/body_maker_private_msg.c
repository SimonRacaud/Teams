/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 body_maker_private_msg.c
*/

#include "database.h"
#include "server.h"
#include "network/response_t.h"

private_msg_t *private_msg_copy(private_msg_t *input)
{
    private_msg_t *copy = malloc(sizeof(private_msg_t));

    if (!copy)
        return NULL;
    memcpy(copy, input, sizeof(private_msg_t));
    return copy;
}

static size_t get_list_size(private_msg_t *ptr, bool is_list)
{
    size_t size = 0;

    if (!is_list) {
        return 1;
    } else {
        for (private_msg_t *node = ptr; node; node = LIST_NEXT(node, entries))
            size++;
        return size;
    }
}

static void write_content(void *body, private_msg_t *private_msg, bool is_list)
{
    bin_private_msg_t *ptr = NULL;
    bin_private_msg_t *packet = NULL;

    ptr = (bin_private_msg_t *) ((char *) body + sizeof(body_header_t));
    for (private_msg_t *node = private_msg; node;
        node = LIST_NEXT(node, entries)) {
        packet = serializer_private_msg_t(node);
        *ptr = *packet;
        free(packet);
        ptr++;
        if (!is_list)
            break;
    }
}

void *body_maker_private_msg(
    private_msg_t *private_msg, bool is_list, const char *logger)
{
    size_t size = get_list_size(private_msg, is_list);
    void *body = NULL;
    body_header_t *head;

    body = malloc(sizeof(body_header_t) + sizeof(bin_private_msg_t) * size);
    if (!body)
        return NULL;
    head = body;
    *head = (body_header_t){.elem_size = sizeof(bin_private_msg_t),
        .list_size = size,
        .entity = "private_msg",
        .logger = ""};
    strncpy(head->logger, logger, SIZE_NAME);
    write_content(body, private_msg, is_list);
    return body;
}
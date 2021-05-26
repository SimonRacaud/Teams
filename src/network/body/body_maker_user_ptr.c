/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 body_make_user_ptr.c
*/

#include "database.h"
#include "server.h"
#include "network/response_t.h"

static size_t get_list_size(user_ptr_t *ptr, bool is_list)
{
    size_t size = 0;

    if (!is_list)
        return 1;

    for (user_ptr_t *node = ptr; node; node = LIST_NEXT(node, entries))
        size++;
    return size;
}

static void write_content(void *body, user_ptr_t *usr, bool is_list)
{
    bin_user_t *packet = NULL;
    bin_user_t *ptr = (bin_user_t *) ((char *) body + sizeof(body_header_t));

    for (user_ptr_t *node = usr; node; node = LIST_NEXT(node, entries), ptr++) {
        packet = serializer_user_t(node->ptr);
        memcpy(ptr, packet, sizeof(bin_user_t));
        free(packet);
        if (!is_list)
            break;
    }
}

void *body_maker_user_ptr(
    user_ptr_t *user_ptr, bool is_list, const char *logger)
{
    size_t size = get_list_size(user_ptr, is_list);
    body_header_t *head;
    void *body = malloc(sizeof(body_header_t) + sizeof(bin_user_t) * size);

    if (!body)
        return NULL;
    head = body;
    *head = (body_header_t){.elem_size = sizeof(bin_user_t),
        .list_size = size,
        .entity = "user",
        .logger = ""};
    strncpy(head->logger, logger, SIZE_NAME);
    write_content(body, user_ptr, is_list);
    return body;
}
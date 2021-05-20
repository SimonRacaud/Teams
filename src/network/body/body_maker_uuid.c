/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 19/05/2021 body_maker_uuid.c
*/

#include "server.h"
#include "network/response_t.h"

void *body_maker_uuid(uuid_t uuid, const char *logger)
{
    body_header_t *header;
    void *body = NULL;
    uuid_t *ptr;

    body = malloc(sizeof(body_header_t) + sizeof(uuid_t));
    if (!body)
        return NULL;
    header = body;
    *header = (body_header_t) {.elem_size = sizeof(uuid_t),
        .list_size = 1, .entity = "uuid", .logger = ""};
    strncpy(header->logger, logger, SIZE_NAME);
    ptr = (uuid_t *)((char *)body + sizeof(body_header_t));
    uuid_copy(*ptr, uuid);
    return body;
}
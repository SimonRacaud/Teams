/*
** EPITECH PROJECT, 2021
** serializer_reply_t.c
** File description:
** serializer_reply_t function
*/

#include <stdlib.h>
#include <string.h>
#include "data/reply_t.h"
#include "save/bin_reply_t.h"

bin_reply_t *serializer_reply_t(const reply_t *src)
{
    bin_reply_t *dest = NULL;

    if (!src)
        return NULL;
    dest = malloc(sizeof(bin_reply_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(bin_reply_t));
    dest->timestamp = src->timestamp;
    uuid_copy(dest->uuid, src->uuid);
    uuid_copy(dest->user_uuid, src->user->uuid);
    // TODO set the vqlue of dest->thread_uuid
    // uuid_copy(dest->thread_uuid, ?);
    memcpy(dest->body, src->body, strlen(src->body));
    return dest;
}
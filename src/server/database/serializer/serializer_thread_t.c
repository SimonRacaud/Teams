/*
** EPITECH PROJECT, 2021
** serializer_thread_t.c
** File description:
** serializer_thread_t function
*/

#include <stdlib.h>
#include <string.h>
#include "data/thread_t.h"
#include "save/bin_thread_t.h"

bin_thread_t *serializer_thread_t(const thread_t *src)
{
    bin_thread_t *dest = NULL;

    if (!src)
        return NULL;
    dest = malloc(sizeof(bin_thread_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(bin_thread_t));
    uuid_copy(dest->uuid, src->uuid);
    uuid_copy(dest->user_uuid, src->user->uuid);
    uuid_copy(dest->channel_uuid, src->parent_channel->uuid);
    dest->timestamp = src->timestamp;
    memcpy(dest->title, src->title, strlen(src->title));
    memcpy(dest->body, src->body, strlen(src->body));
    return dest;
}
/*
** EPITECH PROJECT, 2021
** deserializer_reply_t.c
** File description:
** deserializer_reply_t function
*/

#include "database.h"

reply_t *deserializer_reply_t(const bin_reply_t *src, const database_t *db)
{
    reply_t *dest = NULL;

    if (!src || !db)
        return NULL;
    dest = malloc(sizeof(reply_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(reply_t));
    dest->timestamp = src->timestamp;
    uuid_copy(dest->uuid, src->uuid);
    dest->user = get_user_from_uuid(db, src->user_uuid);
    dest->parent_thread = NULL; // thread_uuid TODO
    if (!dest->user || !dest->parent_thread)
        return NULL;
    memcpy(dest->body, src->body, strlen(src->body));
    return dest;
}
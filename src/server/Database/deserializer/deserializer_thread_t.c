/*
** EPITECH PROJECT, 2021
** deserializer_thread_t.c
** File description:
** deserializer_thread_t function
*/

#include "database.h"

thread_t *deserializer_thread_t(const bin_thread_t *src, const database_t *db)
{
    thread_t *dest = NULL;

    if (!src || !db)
        return NULL;
    dest = malloc(sizeof(thread_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(thread_t));
    uuid_copy(dest->uuid, src->uuid);
    dest->user = get_user_from_uuid(db, src->user_uuid);
    dest->parent_channel = NULL; //parent_channel TODO
    if (!dest->user || !dest->parent_channel)
        return NULL;
    dest->timestamp = src->timestamp;
    memcpy(dest->title, src->title, strlen(src->title));
    memcpy(dest->body, src->body, strlen(src->body));
    return dest;
}
/*
** EPITECH PROJECT, 2021
** deserializer_private_msg_t.c
** File description:
** deserializer_private_msg_t function
*/

#include "database.h"

private_msg_t *deserializer_private_msg_t(
    const bin_private_msg_t *src, const database_t *db)
{
    private_msg_t *dest = NULL;

    if (!src || !db)
        return NULL;
    dest = malloc(sizeof(private_msg_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(private_msg_t));
    dest->timestamp = src->timestamp;
    uuid_copy(dest->uuid, src->uuid);
    dest->receiver = get_user_from_uuid(db, src->receiver_uuid);
    dest->sender = get_user_from_uuid(db, src->sender_uuid);
    memcpy(dest->body, src->body, strlen(src->body));
    return dest;
}
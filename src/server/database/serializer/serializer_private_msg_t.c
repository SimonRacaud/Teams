/*
** EPITECH PROJECT, 2021
** serializer_private_msg_t.c
** File description:
** serializer_private_msg_t function
*/

#include "data/private_msg_t.h"
#include "save/bin_private_msg_t.h"
#include "database.h"

bin_private_msg_t *serializer_private_msg_t(const private_msg_t *src)
{
    bin_private_msg_t *dest = NULL;

    if (!src)
        return NULL;
    dest = malloc(sizeof(bin_private_msg_t));
    if (!dest)
        return NULL;
    bzero(dest, sizeof(bin_private_msg_t));
    dest->timestamp = src->timestamp;
    uuid_copy(dest->uuid, src->uuid);
    if (src->receiver->uuid)
        uuid_copy(dest->receiver_uuid, src->receiver->uuid);
    if (src->sender->uuid)
        uuid_copy(dest->sender_uuid, src->sender->uuid);
    memcpy(dest->body, src->body, strlen(src->body));
    return dest;
}
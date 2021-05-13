/*
** EPITECH PROJECT, 2021
** deserializer_channel_t.c
** File description:
** deserializer_channel_t function
*/

#include <stdlib.h>
#include <string.h>
#include "data/channel_t.h"
#include "data/database_t.h"
#include "save/bin_channel_t.h"

channel_t *deserializer_channel_t(
    const bin_channel_t *src, const database_t *db)
{
    channel_t *dest = NULL;

    if (!src || !db)
        return NULL;
    dest = malloc(sizeof(channel_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(channel_t));
    uuid_copy(dest->uuid, src->uuid);
    memcpy(dest->name, src->name, strlen(src->name));
    memcpy(dest->description, src->description, strlen(src->description));
    return dest;
}
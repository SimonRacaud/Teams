/*
** EPITECH PROJECT, 2021
** serializer_channel_t.c
** File description:
** serializer_channel_t function
*/

#include <stdlib.h>
#include <string.h>
#include "data/channel_t.h"
#include "save/bin_channel_t.h"

bin_channel_t *serializer_channel_t(const channel_t *src)
{
    bin_channel_t *dest = NULL;

    if (!src)
        return NULL;
    dest = malloc(sizeof(bin_channel_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(bin_channel_t));
    uuid_copy(dest->uuid, src->uuid);
    uuid_copy(dest->team_uuid, src->parent_team->uuid);
    memcpy(dest->name, src->name, strlen(src->name));
    memcpy(dest->description, src->description, strlen(src->description));
    return dest;
}
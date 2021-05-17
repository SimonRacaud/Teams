/*
** EPITECH PROJECT, 2021
** deserializer_channel_t.c
** File description:
** deserializer_channel_t function
*/

#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "data/channel_t.h"
#include "data/database_t.h"
#include "save/bin_channel_t.h"

channel_t *deserializer_channel_t(
    const bin_channel_t *src, const database_t *db)
{
    channel_t *dest = NULL;
    uuid_selector_t params = {0};

    if (!src || !db)
        return NULL;
    dest = malloc(sizeof(channel_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(channel_t));
    memset(&params, 0, sizeof(uuid_selector_t));
    uuid_copy(dest->uuid, src->uuid);
    uuid_copy(params.uuid_team, src->team_uuid);
    dest->parent_team = get_team(db, &params);
    if (!dest->parent_team)
        return NULL;
    memcpy(dest->name, src->name, strlen(src->name));
    memcpy(dest->description, src->description, strlen(src->description));
    return dest;
}
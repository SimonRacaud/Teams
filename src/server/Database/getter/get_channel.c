/*
** EPITECH PROJECT, 2021
** get_channel.c
** File description:
** get_channel function
*/

#include "database.h"

channel_t *get_channel(database_t *db, uuid_selector_t *params)
{
    int err = ERROR;
    channel_t *channel = NULL;

    if (!db || !params)
        return NULL;
    if (uuid_is_null(params->uuid_team) || uuid_is_null(params->uuid_channel))
        return NULL;
    channel = get_channel_from_uuid(db, params, &err);
    (void) err;
    return channel;
}
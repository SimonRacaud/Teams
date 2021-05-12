/*
** EPITECH PROJECT, 2021
** get_thread.c
** File description:
** get_thread function
*/

#include "database.h"

static thread_t *get_thread_from_uuid(database_t *db, uuid_selector_t *params)
{
    int err = ERROR;
    channel_t *channel = get_channel_from_uuid(db, params, &err);
    thread_t *thread = NULL;
    
    if (!channel)
        return NULL;
    LIST_FOREACH(thread, &channel->threads, entries) {
        if (!uuid_compare(thread->uuid, params->uuid_thread))
            return thread;
    }
    return NULL;
}

thread_t *get_thread(database_t *db, uuid_selector_t *params)
{
    if (!db || !params)
        return NULL;
    if (uuid_is_null(params->uuid_team) ||
        uuid_is_null(params->uuid_channel) ||
        uuid_is_null(params->uuid_thread))
        return NULL;
    return get_thread_from_uuid(db, params);
}
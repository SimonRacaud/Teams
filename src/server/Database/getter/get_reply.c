/*
** EPITECH PROJECT, 2021
** get_reply.c
** File description:
** get_reply function
*/

#include "database.h"

static reply_t *get_reply_from_uuid(database_t *db, uuid_selector_t *params)
{
    reply_t *reply = NULL;
    thread_t *thread = get_thread(db, params);

    if (!thread)
        return NULL;
    LIST_FOREACH(reply, &thread->replies, entries) {
        if (!uuid_compare(reply->uuid, params->uuid_reply))
            return reply;
    }
    return NULL;
}

reply_t *get_reply(database_t *db, uuid_selector_t *params)
{
    if (!db || !params)
        return NULL;
    if (uuid_is_null(params->uuid_team) ||
        uuid_is_null(params->uuid_channel) ||
        uuid_is_null(params->uuid_thread) ||
        uuid_is_null(params->uuid_reply)
    )
        return NULL;
    return get_reply_from_uuid(db, params);
}
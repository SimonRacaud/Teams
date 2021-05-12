/*
** EPITECH PROJECT, 2021
** get_private_msg.c
** File description:
** get_private_msg function
*/

#include "database.h"

static private_msg_t *get_private_msg_from_uuid(
    database_t *db, uuid_selector_t *params)
{
    private_msg_t *msg = NULL;
    user_t *user = get_user(db, params);

    if (!user)
        return NULL;
    LIST_FOREACH(msg, &user->messages, entries) {
        if (!uuid_compare(msg->uuid, params->uuid_private_msg))
            return msg;
    }
    return NULL;
}

private_msg_t *get_private_msg(database_t *db, uuid_selector_t *params)
{
    if (!db || !params)
        return NULL;
    if (uuid_is_null(params->uuid_user) ||
        uuid_is_null(params->uuid_private_msg))
        return NULL;
    return get_private_msg_from_uuid(db, params);
}
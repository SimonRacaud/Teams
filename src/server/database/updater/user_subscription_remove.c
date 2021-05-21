/*
** EPITECH PROJECT, 2021
** get_private_msg.c
** File description:
** get_private_msg function
*/

#include "database.h"

static int subscription_remove(database_t *db, uuid_selector_t *params)
{
    char team_uuid[UUID_STR];
    char user_uuid[UUID_STR];
    team_t *team = NULL;
    user_t *user = get_user(db, params);

    if (!user)
        return ERR_UNKNOWN_USER;
    LIST_FOREACH(team, &user->teams, entries) {
        if (!uuid_compare(team->uuid, params->uuid_team)) {
            LIST_REMOVE(team, entries);
        }
    }
    uuid_unparse(team->uuid, team_uuid);
    uuid_unparse(user->uuid, user_uuid);
    server_event_user_unsubscribed(team_uuid, user_uuid);
    return SUCCESS;
}

int user_subscription_remove(database_t *db, uuid_selector_t *params)
{
    if (!db || !params)
        return ERROR;
    if (uuid_is_null(params->uuid_user) || uuid_is_null(params->uuid_team))
        return ERROR;
    return subscription_remove(db, params);
}
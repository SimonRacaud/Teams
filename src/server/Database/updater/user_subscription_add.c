/*
** EPITECH PROJECT, 2021
** get_private_msg.c
** File description:
** get_private_msg function
*/

#include "database.h"

static int subscription_add(database_t *db, uuid_selector_t *params)
{
    team_t *team = get_team(db, params);
    user_t *user = get_user(db, params);

    if (!team || !user)
        return (!team) ? ERR_UNKNOWN_TEAM : ERR_UNKNOWN_USER;
    LIST_INSERT_HEAD(&user->teams, team, entries);
    return SUCCESS;
}

int user_subscription_add(database_t *db, uuid_selector_t *params)
{
    if (!db || !params)
        return ERROR;
    if (uuid_is_null(params->uuid_user) || uuid_is_null(params->uuid_team))
        return ERROR;
    return subscription_add(db, params);
}
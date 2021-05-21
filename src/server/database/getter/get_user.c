/*
** EPITECH PROJECT, 2021
** get_user.c
** File description:
** get_user function
*/

#include "database.h"

user_t *get_user(const database_t *db, uuid_selector_t *params)
{
    if (!db || !params)
        return NULL;
    if (uuid_is_null(params->uuid_user))
        return NULL;
    return get_user_from_uuid(db, params->uuid_user);
}

size_t get_nb_subscribed_teams(const database_t *db)
{
    size_t nbr = 0;
    user_t *user;

    LIST_FOREACH(user, &db->users, entries)
    {
        nbr += get_nb_team_from_user(user);
    }
    return nbr;
}
/*
** EPITECH PROJECT, 2021
** get_team.c
** File description:
** get_team function
*/

#include "database.h"

team_t *get_team(const database_t *db, uuid_selector_t *params)
{
    team_t *team = NULL;
    
    if (!db || !params)
        return NULL;
    if (uuid_is_null(params->uuid_team))
        return NULL;
    team = get_match_team(db, params);
    return team;
}
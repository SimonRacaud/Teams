/*
** EPITECH PROJECT, 2021
** create_team.c
** File description:
** create_team function
*/

#include "database.h"

static void init_team_node(team_t *node, const char *teamname, const char *desc)
{
    memset(node, 0, sizeof(team_t));
    memcpy(node->name, teamname, strlen(teamname));
    memcpy(node->description, desc, strlen(desc));
    uuid_generate(node->uuid);
}

static void event(uuid_t team, const char *name, uuid_t user)
{
    char team_uuid[UUID_STR];
    char user_uuid[UUID_STR];

    uuid_unparse(team, team_uuid);
    uuid_unparse(user, user_uuid);
    server_event_team_created(team_uuid, name, user_uuid);
}

rcode_e create_team(database_t *db, const char *teamname,
const char *desc, uuid_selector_t *params)
{
    team_t *node = NULL;

    if (!db || !teamname || !desc)
        return ERROR;
    if (strlen(teamname) > SIZE_NAME || strlen(desc) > SIZE_DESC)
        return ERROR;
    node = malloc(sizeof(team_t));
    if (!node)
        return ERROR;
    init_team_node(node, teamname, desc);
    LIST_INSERT_HEAD(&db->teams, node, entries);
    uuid_copy(params->uuid_team, node->uuid);
    event(node->uuid, teamname, params->uuid_user);
    return SUCCESS;
}
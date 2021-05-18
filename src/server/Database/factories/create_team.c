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
    return SUCCESS;
}
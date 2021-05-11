/*
** EPITECH PROJECT, 2021
** create_team.c
** File description:
** create_team function
*/

#include "database.h"

static bool already_exist(database_t *db, const char *teamname)
{
    team_t *node = NULL;

    LIST_FOREACH(node, &db->teams, entries) {
        if (!strcmp(node->name, teamname))
            return true;
    }
    return false;
}

static void init_team_node(team_t *node, const char *teamname, const char *desc)
{
    memset(node, 0, sizeof(team_t));
    memcpy(node->name, teamname, strlen(teamname));
    memcpy(node->description, desc, strlen(desc));
    uuid_generate(node->uuid);
}

int create_team(database_t *db, const char *teamname,
const char *desc, __attribute__((unused)) uuid_selector_t *params)
{
    team_t *node = NULL;

    if (!db || !teamname || !desc)
        return ERROR;
    if (strlen(teamname) > SIZE_NAME || strlen(desc) > SIZE_DESC)
        return ERROR;
    if (already_exist(db, teamname))
        return ERR_ALREADY_EXIST;
    node = malloc(sizeof(team_t));
    if (!node)
        return ERROR;
    init_team_node(node, teamname, desc);
    LIST_INSERT_HEAD(&db->teams, node, entries);
    return SUCCESS;
}
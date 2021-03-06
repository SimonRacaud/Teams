/*
** EPITECH PROJECT, 2021
** create_channel.c
** File description:
** create_channel function
*/

#include "database.h"

team_t *get_match_team(const database_t *db, uuid_selector_t *params)
{
    team_t *node = NULL;

    LIST_FOREACH(node, &db->teams, entries)
    {
        if (!uuid_compare(node->uuid, params->uuid_team))
            return node;
    }
    return NULL;
}

static bool is_correct_params(
    database_t *db, uuid_selector_t *params, int *err_val, const char *name)
{
    team_t *node = NULL;
    channel_t *channel = NULL;
    team_t *team = get_match_team(db, params);

    if (!team) {
        *err_val = ERR_UNKNOWN_TEAM;
        return false;
    }
    LIST_FOREACH(node, &db->teams, entries) {
        LIST_FOREACH(channel, &node->channels, entries) {
            if (strcmp(name, channel->name) == 0) {
                *err_val = ERR_ALREADY_EXIST;
                return false;
            }
        }
    }
    return true;
}

static void init_channel_node(channel_t *node, const char *channelname,
    const char *desc, uuid_selector_t *params)
{
    char uuid_team[UUID_STR];
    char uuid_channel[UUID_STR];

    bzero(node, sizeof(channel_t));
    memcpy(node->name, channelname, strlen(channelname));
    memcpy(node->description, desc, strlen(desc));
    uuid_generate(node->uuid);
    uuid_copy(params->uuid_channel, node->uuid);
    uuid_unparse(params->uuid_team, uuid_team);
    uuid_unparse(node->uuid, uuid_channel);
    server_event_channel_created(uuid_team, uuid_channel, channelname);
}

static int inset_channel(
    channel_t *node, database_t *db, uuid_selector_t *params)
{
    team_t *team = get_match_team(db, params);

    if (!team)
        return ERR_UNKNOWN_TEAM;
    node->parent_team = team;
    LIST_INSERT_HEAD(&team->channels, node, entries);
    return SUCCESS;
}

rcode_e create_channel(database_t *db, const char *channelname,
    const char *desc, uuid_selector_t *params)
{
    int err_val = ERROR;
    channel_t *node = NULL;

    if (!db || !channelname || !desc || !params)
        return ERROR;
    if (strlen(channelname) > SIZE_NAME || strlen(desc) > SIZE_DESC)
        return ERROR;
    if (uuid_is_null(params->uuid_team))
        return ERROR;
    if (!is_correct_params(db, params, &err_val, channelname))
        return err_val;
    node = malloc(sizeof(channel_t));
    if (!node)
        return ERROR;
    init_channel_node(node, channelname, desc, params);
    return inset_channel(node, db, params);
}
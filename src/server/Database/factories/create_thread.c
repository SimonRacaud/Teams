/*
** EPITECH PROJECT, 2021
** create_thread.c
** File description:
** create_thread function
*/

#include "database.h"

channel_t *get_channel_from_uuid(const database_t *db,
uuid_selector_t *params, int *err)
{
    team_t *team = get_match_team(db, params);
    channel_t *channel = NULL;

    if (!team) {
        *err = ERR_UNKNOWN_TEAM;
        return NULL;
    }
    LIST_FOREACH(channel, &team->channels, entries) {
        if (!uuid_compare(channel->uuid, params->uuid_channel))
            return channel;
    }
    *err = ERR_UNKNOWN_CHANNEL;
    return NULL;
}

static void init_thread_node(channel_t *channel,
const char *title, const char *body)
{
    thread_t *node = malloc(sizeof(thread_t));

    memset(node, 0, sizeof(thread_t));
    memcpy(node->title, title, strlen(title));
    memcpy(node->body, body, strlen(body));
    node->timestamp = time(NULL);
    uuid_generate(node->uuid);
    LIST_INSERT_HEAD(&channel->threads, node, entries);
}

int create_thread(database_t *db,
const char *title, const char *body, uuid_selector_t *params)
{
    int err = ERROR;
    channel_t *channel = NULL;

    if (!db || !title || !body || !params)
        return ERROR;
    if (strlen(body) > SIZE_BODY || strlen(title) > SIZE_NAME)
        return ERROR;
    if (uuid_is_null(params->uuid_team) || uuid_is_null(params->uuid_channel))
        return ERROR;
    channel = get_channel_from_uuid(db, params, &err);
    if (!channel)
        return err;
    init_thread_node(channel, title, body);
    return SUCCESS;
}
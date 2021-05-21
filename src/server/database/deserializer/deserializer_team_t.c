/*
** EPITECH PROJECT, 2021
** deserializer_team_t.c
** File description:
** deserializer_team_t function
*/

#include <stdlib.h>
#include <string.h>
#include "data/team_t.h"
#include "data/database_t.h"
#include "save/bin_team_t.h"
#include "database.h"

team_t *deserializer_team_t(const bin_team_t *src, const database_t *db)
{
    team_t *dest = NULL;

    if (!src || !db)
        return NULL;
    dest = malloc(sizeof(team_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(team_t));
    uuid_copy(dest->uuid, src->uuid);
    memcpy(dest->name, src->name, strlen(src->name));
    memcpy(dest->description, src->description, strlen(src->description));
    LIST_INIT(&dest->channels);
    LIST_INIT(&dest->users);
    return dest;
}

bool deserialize_all_teams(const database_save_t *db_save, database_t *db)
{
    team_t *team;
    channel_t **channels;

    for (uint i = 0; i < db_save->head->nb_team; i++) {
        team = deserializer_team_t(db_save->teams[i], db);
        if (team == NULL)
            return false;
        LIST_INSERT_HEAD(&db->teams, team, entries);
    }

    channels = deserialize_all_channels(db_save, db);
    if (channels == NULL)
        return NULL;
    team = NULL;
    LIST_FOREACH(team, &db->teams, entries)
    for (uint i = 0; i < db_save->head->nb_channel; i++)
        if (!uuid_compare(team->uuid, channels[i]->parent_team->uuid))
            LIST_INSERT_HEAD(&team->channels, channels[i], entries);
    free(channels);
    return true;
}
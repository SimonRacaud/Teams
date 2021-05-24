/*
** EPITECH PROJECT, 2021
** deserializer_channel_t.c
** File description:
** deserializer_channel_t function
*/

#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "data/channel_t.h"
#include "data/database_t.h"
#include "save/bin_channel_t.h"

channel_t *deserializer_channel_t(
    const bin_channel_t *src, const database_t *db)
{
    channel_t *dest = NULL;
    uuid_selector_t params = {0};

    if (!src || !db)
        return NULL;
    dest = malloc(sizeof(channel_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(channel_t));
    memset(&params, 0, sizeof(uuid_selector_t));
    uuid_copy(dest->uuid, src->uuid);
    uuid_copy(params.uuid_team, src->team_uuid);
    dest->parent_team = get_team(db, &params);
    if (!dest->parent_team)
        return NULL;
    memcpy(dest->name, src->name, strlen(src->name));
    memcpy(dest->description, src->description, strlen(src->description));
    LIST_INIT(&dest->threads);
    return dest;
}

static inline void destroy_created_result(channel_t **result, uint max_index)
{
    for (uint i = 0; i < max_index; i++)
        free(result[i]);
    free(result);
}

static bool fill_channels_threads(
    const database_save_t *db_save, const database_t *db, channel_t **result)
{
    thread_t **threads = deserialize_all_threads(db_save, db, result);
    char thread_uuid[UUID_STR];
    char channel_uuid[UUID_STR];

    if (threads == NULL)
        return false;
    for (uint i = 0; i < db_save->head->nb_channel; i++)
        for (uint k = 0; k < db_save->head->nb_thread; k++)
            if (!uuid_compare(
                    result[i]->uuid, threads[k]->parent_channel->uuid)) {
                LIST_INSERT_HEAD(&result[i]->threads, threads[k], entries);
                uuid_unparse(threads[k]->uuid, thread_uuid);
                uuid_unparse(result[i]->uuid, channel_uuid);
                printf("Thread (%s) linked to channel (%s)\n", thread_uuid,
                    channel_uuid);
            }
    free(threads);
    return true;
}

channel_t **deserialize_all_channels(
    const database_save_t *db_save, const database_t *db)
{
    channel_t **result = calloc(db_save->head->nb_channel, sizeof(channel_t *));
    char uuid[UUID_STR];

    if (result == NULL)
        return NULL;
    for (uint i = 0; i < db_save->head->nb_channel; i++) {
        result[i] = deserializer_channel_t(db_save->channels[i], db);
        if (result[i] == NULL) {
            destroy_created_result(result, i);
            return NULL;
        }
        uuid_unparse(result[i]->uuid, uuid);
        printf("Channel loaded: %s\n", uuid);
    }
    if (!fill_channels_threads(db_save, db, result)) {
        destroy_created_result(result, db_save->head->nb_channel);
        return NULL;
    }
    return result;
}
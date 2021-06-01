/*
** EPITECH PROJECT, 2021
** deserializer_thread_t.c
** File description:
** deserializer_thread_t function
*/

#include "database.h"

thread_t *deserializer_thread_t(const bin_thread_t *src, const database_t *db,
    const database_save_t *db_save, channel_t **channels)
{
    thread_t *dest = NULL;

    if (!src || !db)
        return NULL;
    dest = malloc(sizeof(thread_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(thread_t));
    uuid_copy(dest->uuid, src->uuid);
    dest->user = get_user_from_uuid(db, src->user_uuid);
    dest->parent_channel = get_channel_by_uuid(
        channels, db_save->head->nb_channel, src->channel_uuid);
    if (!dest->user || !dest->parent_channel)
        return NULL;
    dest->timestamp = src->timestamp;
    memcpy(dest->title, src->title, strlen(src->title));
    memcpy(dest->body, src->body, strlen(src->body));
    LIST_INIT(&dest->replies);
    return dest;
}

static void destroy_created_result(thread_t **result, uint max_index)
{
    for (uint i = 0; i < max_index; i++)
        free(result[i]);
    free(result);
}

static bool fill_threads_replies(
    const database_save_t *db_save, const database_t *db, thread_t **result)
{
    reply_t **replies = deserialize_all_replies(db_save, db, result);
    char reply_uuid[UUID_STR];
    char thread_uuid[UUID_STR];

    if (replies == NULL)
        return false;
    for (uint i = 0; i < db_save->head->nb_thread; i++)
        for (uint k = 0; k < db_save->head->nb_reply; k++)
            if (!uuid_compare(
                    result[i]->uuid, replies[k]->parent_thread->uuid)) {
                LIST_INSERT_HEAD(&result[i]->replies, replies[k], entries);
                uuid_unparse(replies[k]->uuid, reply_uuid);
                uuid_unparse(result[i]->uuid, thread_uuid);
                printf("Reply (%s) linked to thread (%s)\n", reply_uuid,
                    thread_uuid);
            }
    free(replies);
    return true;
}

thread_t **deserialize_all_threads(
    const database_save_t *db_save, const database_t *db, channel_t **channels)
{
    thread_t **result = calloc(db_save->head->nb_thread, sizeof(thread_t *));
    char uuid[UUID_STR];

    if (result == NULL)
        return NULL;
    for (uint i = 0; i < db_save->head->nb_thread; i++) {
        result[i] =
            deserializer_thread_t(db_save->threads[i], db, db_save, channels);
        if (result[i] == NULL) {
            destroy_created_result(result, i);
            return NULL;
        }
        uuid_unparse(result[i]->uuid, uuid);
        printf("Thread loaded: %s\n", uuid);
    }
    if (!fill_threads_replies(db_save, db, result)) {
        destroy_created_result(result, db_save->head->nb_thread);
        return NULL;
    }
    return result;
}
/*
** EPITECH PROJECT, 2021
** deserializer_reply_t.c
** File description:
** deserializer_reply_t function
*/

#include "database.h"

reply_t *deserializer_reply_t(const bin_reply_t *src, const database_t *db,
    const database_save_t *db_save, thread_t **threads)
{
    reply_t *dest = NULL;

    if (!src || !db)
        return NULL;
    dest = malloc(sizeof(reply_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(reply_t));
    dest->timestamp = src->timestamp;
    uuid_copy(dest->uuid, src->uuid);
    dest->user = get_user_from_uuid(db, src->user_uuid);
    dest->parent_thread =
        get_thread_by_uuid(threads, db_save->head->nb_thread, src->thread_uuid);
    if (!dest->user || !dest->parent_thread)
        return NULL;
    memcpy(dest->body, src->body, strlen(src->body));
    return dest;
}

static inline void destroy_created_result(reply_t **result, uint max_index)
{
    for (uint i = 0; i < max_index; i++)
        free(result[i]);
    free(result);
}

reply_t **deserialize_all_replies(
    const database_save_t *db_save, const database_t *db, thread_t **threads)
{
    reply_t **result = calloc(db_save->head->nb_reply, sizeof(reply_t *));
    char uuid[UUID_STR];

    if (result == NULL)
        return NULL;
    for (uint i = 0; i < db_save->head->nb_reply; i++) {
        result[i] =
            deserializer_reply_t(db_save->replies[i], db, db_save, threads);
        if (result[i] == NULL) {
            destroy_created_result(result, i);
            return NULL;
        }
        uuid_unparse(result[i]->uuid, uuid);
        printf("Reply loaded: %s\n", uuid);
    }
    return result;
}
/*
** EPITECH PROJECT, 2021
** deserializer_private_msg_t.c
** File description:
** deserializer_private_msg_t function
*/

#include "database.h"

private_msg_t *deserializer_private_msg_t(
    const bin_private_msg_t *src, const database_t *db)
{
    private_msg_t *dest = NULL;

    if (!src || !db)
        return NULL;
    dest = malloc(sizeof(private_msg_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(private_msg_t));
    dest->timestamp = src->timestamp;
    uuid_copy(dest->uuid, src->uuid);
    dest->receiver = get_user_from_uuid(db, src->receiver_uuid);
    dest->sender = get_user_from_uuid(db, src->sender_uuid);
    memcpy(dest->body, src->body, strlen(src->body));
    return dest;
}

static inline void destroy_created_result(
    private_msg_t **result, uint max_index)
{
    for (uint i = 0; i < max_index; i++)
        free(result[i]);
    free(result);
}

private_msg_t **deserialize_all_private_msg(
    const database_save_t *db_save, const database_t *db)
{
    private_msg_t **result =
        calloc(db_save->head->nb_private_msg, sizeof(private_msg_t *));
    char uuid[UUID_STR];

    if (result == NULL)
        return NULL;
    for (uint i = 0; i < db_save->head->nb_private_msg; i++) {
        result[i] = deserializer_private_msg_t(db_save->messages[i], db);
        if (result[i] == NULL) {
            destroy_created_result(result, i);
            return NULL;
        }
        uuid_unparse(result[i]->uuid, uuid);
        printf("Private message loaded: %s\n", uuid);
    }
    return result;
}
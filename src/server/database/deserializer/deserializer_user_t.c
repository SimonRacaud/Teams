/*
** EPITECH PROJECT, 2021
** deserializer_user_t.c
** File description:
** deserializer_user_t function
*/

#include <stdlib.h>
#include <string.h>
#include "data/user_t.h"
#include "data/database_t.h"
#include "save/bin_user_t.h"
#include "database.h"

user_t *deserializer_user_t(const bin_user_t *src, const database_t *db)
{
    user_t *dest = NULL;

    if (!src || !db)
        return NULL;
    dest = malloc(sizeof(user_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(user_t));
    uuid_copy(dest->uuid, src->uuid);
    dest->status = src->status;
    memcpy(dest->username, src->name, strlen(src->name));
    LIST_INIT(&dest->teams);
    LIST_INIT(&dest->messages);
    return dest;
}

static bool fill_user_private_msg(
    const database_save_t *db_save, database_t *db)
{
    private_msg_t **pm_list = deserialize_all_private_msg(db_save, db);
    user_t *user;
    char user_uuid[UUID_STR];
    char pm_uuid[UUID_STR];

    if (pm_list == NULL)
        return false;
    for (uint i = 0; i < db_save->head->nb_private_msg; i++)
        LIST_FOREACH(user, &db->users, entries)
        {
            if (!uuid_compare(user->uuid, pm_list[i]->receiver->uuid)) {
                LIST_INSERT_HEAD(&user->messages, pm_list[i], entries);
                uuid_unparse(user->uuid, user_uuid);
                uuid_unparse(pm_list[i]->uuid, pm_uuid);
                printf("Private message (%s) linked to user (%s)\n", pm_uuid,
                    user_uuid);
            }
        }
    free(pm_list);
    return true;
}

bool deserialize_all_users(const database_save_t *db_save, database_t *db)
{
    user_t *user;
    char uuid[UUID_STR];

    for (uint i = 0; i < db_save->head->nb_user; i++) {
        user = deserializer_user_t(db_save->users[i], db);
        if (user == NULL)
            return false;
        uuid_unparse(user->uuid, uuid);
        server_event_user_loaded(uuid, user->username);
        LIST_INSERT_HEAD(&db->users, user, entries);
        printf("User loaded: %s\n", uuid);
    }
    if (!fill_user_private_msg(db_save, db))
        return false;
    return true;
}
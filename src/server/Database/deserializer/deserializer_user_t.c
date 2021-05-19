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

static bool fill_user_teams(const database_save_t *db_save, database_t *db,
    user_t *user, uint user_index)
{
    team_t *team;
    uint teams_index = 0;
    uuid_selector_t params = {0};

    memset(&params, 0, sizeof(uuid_selector_t));
    for (uint k = 0; k < db_save->users[user_index]->nb_subscribed_teams;
         k++, teams_index++) {
        uuid_copy(params.uuid_team, *db_save->user_teams_list[teams_index]);
        team = get_team(db, &params);
        if (team == NULL)
            return false;
        LIST_INSERT_HEAD(&team->users, user, entries);
        LIST_INSERT_HEAD(&user->teams, team, entries);
    }
    return true;
}

static bool fill_user_private_msg(
    const database_save_t *db_save, database_t *db)
{
    private_msg_t **pm_list = deserialize_all_private_msg(db_save, db);
    user_t *user;

    if (pm_list == NULL)
        return false;
    for (uint i = 0; i < db_save->head->nb_private_msg; i++)
        LIST_FOREACH(user, &db->users, entries)
        {
            if (!uuid_compare(user->uuid, pm_list[i]->receiver->uuid))
                LIST_INSERT_HEAD(&user->messages, pm_list[i], entries);
        }
    free(pm_list);
    return true;
}

bool deserialize_all_users(const database_save_t *db_save, database_t *db)
{
    user_t *user;

    for (uint i = 0; i < db_save->head->nb_user; i++) {
        user = deserializer_user_t(db_save->users[i], db);
        if (user == NULL)
            return false;
        if (!fill_user_teams(db_save, db, user, i))
            return false;
        LIST_INSERT_HEAD(&db->users, user, entries);
    }
    if (!fill_user_private_msg(db_save, db))
        return false;
    return true;
}
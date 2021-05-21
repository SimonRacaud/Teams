/*
** EPITECH PROJECT, 2021
** loader
** File description:
** convert_database.c - Created: 18/05/2021
*/

#include "database.h"

void create_empty_database(database_t *db)
{
    memset(db, 0, sizeof(database_t));

    LIST_INIT(&db->users);
    LIST_INIT(&db->teams);
}

static bool fill_user_teams(const database_save_t *db_save, database_t *db,
    user_t *user, uint user_index)
{
    team_t *team;
    uuid_selector_t params = {0};

    bzero(&params, sizeof(uuid_selector_t));
    for (uint k = 0; k < db_save->users[user_index]->nb_subscribed_teams; k++) {
        uuid_copy(params.uuid_team, db_save->user_teams_list[user_index][k]);
        team = get_team(db, &params);
        if (team == NULL)
            return false;
        LIST_INSERT_HEAD(&team->users, user, entries);
        LIST_INSERT_HEAD(&user->teams, team, entries);
    }
    return true;
}

static bool get_users_to_fill_teams(
    const database_save_t *db_save, database_t *db)
{
    user_t *user;

    for (uint i = 0; i < db_save->head->nb_user; i++) {
        user = get_user_from_uuid(db, db_save->users[i]->uuid);
        if (!fill_user_teams(db_save, db, user, i))
            return false;
    }
    return true;
}

bool convert_saved_db_to_release_db(
    const database_save_t *db_save, database_t *db)
{
    if (!deserialize_all_users(db_save, db))
        return false;
    if (!deserialize_all_teams(db_save, db))
        return false;
    if (!get_users_to_fill_teams(db_save, db))
        return false;
    return true;
}
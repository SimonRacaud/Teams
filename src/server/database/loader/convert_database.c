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
    user_ptr_t *user_ptr;
    team_ptr_t *team_ptr;
    uuid_selector_t params = {0};

    bzero(&params, sizeof(uuid_selector_t));
    for (uint k = 0; k < db_save->users[user_index]->nb_subscribed_teams; k++) {
        uuid_copy(params.uuid_team, db_save->user_teams_list[user_index][k]);
        team = get_team(db, &params);
        user_ptr = malloc(sizeof(user_ptr_t));
        team_ptr = malloc(sizeof(team_ptr_t));
        if (team == NULL || user_ptr == NULL || team_ptr == NULL)
            return false;
        user_ptr->ptr = user;
        team_ptr->ptr = team;
        LIST_INSERT_HEAD(&team->users, user_ptr, entries);
        LIST_INSERT_HEAD(&user->teams, team_ptr, entries);
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
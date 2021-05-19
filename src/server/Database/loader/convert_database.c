/*
** EPITECH PROJECT, 2021
** loader
** File description:
** convert_database.c - Created: 18/05/2021
*/

#include "database.h"

database_t *create_empty_database(void)
{
    database_t *db = malloc(sizeof(database_t));

    if (db == NULL)
        return NULL;
    memset(db, 0, sizeof(database_t));

    LIST_INIT(&db->users);
    LIST_INIT(&db->teams);

    return db;
}

database_t *convert_saved_db_to_release_db(const database_save_t *db_save)
{
    database_t *db = create_empty_database();

    if (db == NULL)
        return NULL;
    if (!deserialize_all_teams(db_save, db))
        return NULL;
    if (!deserialize_all_users(db_save, db))
        return NULL;
    return db;
}
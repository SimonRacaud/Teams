/*
** EPITECH PROJECT, 2021
** loader
** File description:
** convert_database.c - Created: 18/05/2021
*/

#include "database.h"

database_t *convert_to_database(const database_save_t *db_save)
{
    database_t *db = malloc(sizeof(database_t));

    if (db == NULL)
        return NULL;
    LIST_INIT(&db->users);
    LIST_INIT(&db->teams);
    if (!deserialize_all_teams(db_save, db))
        return NULL;
    if (!deserialize_all_users(db_save, db))
        return NULL;
    return db;
}
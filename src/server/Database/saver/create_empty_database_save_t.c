/*
** EPITECH PROJECT, 2021
** saver
** File description:
** create_empty_database_save_t.c - Created: 19/05/2021
*/

#include "database.h"

static void init_database_save(database_save_t *db)
{
    memset(db->users, 0, sizeof(bin_user_t *) * db->head->nb_user);
    memset(db->user_teams_list, 0, sizeof(uuid_t *) * db->head->nb_user);
    memset(db->teams, 0, sizeof(bin_team_t *) * db->head->nb_team);
    memset(db->channels, 0, sizeof(bin_channel_t *) * db->head->nb_channel);
    memset(db->threads, 0, sizeof(bin_thread_t *) * db->head->nb_thread);
    memset(db->replies, 0, sizeof(bin_reply_t *) * db->head->nb_reply);
    memset(db->messages, 0,
        sizeof(bin_private_msg_t *) * db->head->nb_private_msg);
}

static bool is_empty_database_save_null(const database_save_t *db)
{
    return !db || !db->users || !db->user_teams_list || !db->teams
        || !db->channels || !db->threads || !db->replies || !db->messages;
}

static bool init_header(database_save_t *db, bin_header_t *buffer)
{
    memset(db, 0, sizeof(database_save_t));
    db->head = malloc(sizeof(bin_header_t));
    if (!db->head) {
        free(db);
        return false;
    }
    memcpy(db->head, buffer, sizeof(bin_header_t));
    return true;
}

database_save_t *create_empty_database_save(bin_header_t *buffer)
{
    database_save_t *db = malloc(sizeof(database_save_t));

    if (db == NULL)
        return NULL;
    if (!init_header(db, buffer))
        return NULL;
    printf("users: %d\n", db->head->nb_user);
    printf("teams: %d\n", db->head->nb_team);
    printf("threads: %d\n", db->head->nb_thread);
    printf("replies: %d\n", db->head->nb_reply);
    printf("messages: %d\n", db->head->nb_private_msg);
    printf("channels: %d\n", db->head->nb_channel);
    db->users = malloc(sizeof(bin_user_t *) * db->head->nb_user);
    db->user_teams_list = malloc(sizeof(uuid_t *) * db->head->nb_user);
    db->teams = malloc(sizeof(bin_team_t *) * db->head->nb_team);
    db->channels = malloc(sizeof(bin_channel_t *) * db->head->nb_channel);
    db->threads = malloc(sizeof(bin_thread_t *) * db->head->nb_thread);
    db->replies = malloc(sizeof(bin_reply_t *) * db->head->nb_reply);
    db->messages =
        malloc(sizeof(bin_private_msg_t *) * db->head->nb_private_msg);
    if (is_empty_database_save_null(db))
        return NULL;
    init_database_save(db);
    return db;
}
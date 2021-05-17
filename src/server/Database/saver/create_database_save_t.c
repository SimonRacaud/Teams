/*
** EPITECH PROJECT, 2021
** create_database_save_t.c
** File description:
** create_database_save_t function
*/

#include "database.h"

static bool init_checker(const database_t *db, database_save_t *dest)
{
    bin_header_t header = {0};

    if (!dest->users || !dest->teams || !dest->channels || !dest->threads
        || !dest->replies || !dest->messages || !dest->user_teams_list)
        return false;
    memset(&header, 0, sizeof(bin_header_t));
    memset(dest->users, 0, sizeof(bin_user_t *) * dest->head->nb_user);
    memset(dest->user_teams_list, 0, sizeof(uuid_t *) * dest->head->nb_user);
    memset(dest->teams, 0, sizeof(bin_team_t *) * dest->head->nb_team);
    memset(dest->channels, 0, sizeof(bin_channel_t *) * dest->head->nb_channel);
    memset(dest->threads, 0, sizeof(bin_thread_t *) * dest->head->nb_thread);
    memset(dest->replies, 0, sizeof(bin_reply_t *) * dest->head->nb_reply);
    memset(dest->messages, 0,
        sizeof(bin_private_msg_t *) * dest->head->nb_private_msg);
    return run_fill_data(db, &header, dest);
}

static bool init_database_save_t(const database_t *db, database_save_t *dest)
{
    dest->head = serializer_header_t(db);
    if (!dest->head)
        return false;
    dest->users = malloc(sizeof(bin_user_t *) * dest->head->nb_user);
    dest->user_teams_list = malloc(sizeof(uuid_t *) * dest->head->nb_user);
    dest->teams = malloc(sizeof(bin_team_t *) * dest->head->nb_team);
    dest->channels = malloc(sizeof(bin_channel_t *) * dest->head->nb_channel);
    dest->threads = malloc(sizeof(bin_thread_t *) * dest->head->nb_thread);
    dest->replies = malloc(sizeof(bin_reply_t *) * dest->head->nb_reply);
    dest->messages =
        malloc(sizeof(bin_private_msg_t *) * dest->head->nb_private_msg);
    if (!init_checker(db, dest))
        return false;
    return true;
}

database_save_t *create_database_save_t(const database_t *db)
{
    database_save_t *dest = NULL;

    if (!db)
        return NULL;
    dest = malloc(sizeof(database_save_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(database_save_t));
    if (!init_database_save_t(db, dest))
        return NULL;
    return dest;
}
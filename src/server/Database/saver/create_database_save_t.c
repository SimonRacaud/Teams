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

static void free_bin_list(const void **list, uint size)
{
    for (uint i = 0; list && i < size; i++)
        free((void *) list[i]);
    free((void *) list);
}

void destroy_database_save_t(const database_save_t *db)
{
    size_t team_offset = 0;

    for (uint i = 0; db->user_teams_list && db->users && i < db->head->nb_user;
         i++)
        for (uint k = 0; k < db->users[i]->nb_subscribed_teams;
             k++, team_offset++)
            free(db->user_teams_list[team_offset]);
    free(db->user_teams_list);
    free_bin_list((const void **) db->users, db->head->nb_user);
    free_bin_list((const void **) db->teams, db->head->nb_team);
    free_bin_list((const void **) db->channels, db->head->nb_channel);
    free_bin_list((const void **) db->threads, db->head->nb_thread);
    free_bin_list((const void **) db->replies, db->head->nb_reply);
    free_bin_list((const void **) db->messages, db->head->nb_private_msg);
    free(db->head);
    free((database_save_t *) db);
}
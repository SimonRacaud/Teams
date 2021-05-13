/*
** EPITECH PROJECT, 2021
** create_database_save_t.c
** File description:
** create_database_save_t function
*/

#include "database.h"
#include "save/database_save_t.h"

static bool init_checker(database_save_t *dest)
{
    if (!dest->users || !dest->teams || !dest->channels || !dest->threads ||
        !dest->replies || !dest->messages || !dest->user_teams_list)
        return false;
    memset(dest->users, 0, sizeof(bin_user_t *) * dest->head->nb_user);
    //memset(dest->user_teams_list, 0, ?); TODO
    memset(dest->teams, 0, sizeof(bin_team_t *) * dest->head->nb_team);
    memset(dest->channels, 0, sizeof(bin_channel_t *) * dest->head->nb_channel);
    memset(dest->threads, 0, sizeof(bin_thread_t *) * dest->head->nb_thread);
    memset(dest->replies, 0, sizeof(bin_reply_t *) * dest->head->nb_reply);
    memset(dest->messages, 0,
    sizeof(bin_private_msg_t *) * dest->head->nb_private_msg);
    return true;
}

static bool init_database_save_t(const database_t *db, database_save_t *dest)
{
    dest->head = serializer_header_t(db);
    if (!dest->head)
        return false;
    dest->users = malloc(sizeof(bin_user_t *) * dest->head->nb_user);
    //dest->user_teams_list; TODO a quoi cela sert et que dois-je mettre dedans
    dest->teams = malloc(sizeof(bin_team_t *) * dest->head->nb_team);
    dest->channels = malloc(sizeof(bin_channel_t *) * dest->head->nb_channel);
    dest->threads = malloc(sizeof(bin_thread_t *) * dest->head->nb_thread);
    dest->replies = malloc(sizeof(bin_reply_t *) * dest->head->nb_reply);
    dest->messages =
    malloc(sizeof(bin_private_msg_t *) * dest->head->nb_private_msg);
    if (!init_checker(dest))
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
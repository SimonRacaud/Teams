/*
** EPITECH PROJECT, 2021
** run_fill_data.c
** File description:
** run_fill_data function
*/

#include "database.h"

static bool run_fill_private_msg(
    user_t *user, bin_header_t *dest, database_save_t *db_save)
{
    private_msg_t *msg = NULL;
    team_ptr_t *user_team = NULL;
    size_t pos = 0;

    LIST_FOREACH(msg, &user->messages, entries)
    {
        db_save->messages[dest->nb_private_msg] = serializer_private_msg_t(msg);
        if (!db_save->messages[dest->nb_private_msg])
            return false;
        dest->nb_private_msg++;
    }
    db_save->user_teams_list[dest->nb_user] =
        malloc(sizeof(uuid_t) * get_nb_team_from_user(user));
    if (!db_save->user_teams_list[dest->nb_user])
        return false;
    LIST_FOREACH(user_team, &user->teams, entries)
    uuid_copy(
        db_save->user_teams_list[dest->nb_user][pos++], user_team->ptr->uuid);
    return true;
}

static bool run_fill_reply(
    thread_t *thread, bin_header_t *dest, database_save_t *db_save)
{
    reply_t *reply = NULL;

    if (thread) {
        LIST_FOREACH(reply, &thread->replies, entries)
        {
            db_save->replies[dest->nb_reply] = serializer_reply_t(reply);
            if (!db_save->replies[dest->nb_reply])
                return false;
            dest->nb_reply++;
        }
    }
    return true;
}

static bool run_fill_thread(
    channel_t *channel, bin_header_t *dest, database_save_t *db_save)
{
    thread_t *thread = NULL;

    if (channel) {
        LIST_FOREACH(thread, &channel->threads, entries)
        {
            if (!run_fill_reply(thread, dest, db_save))
                return false;
            db_save->threads[dest->nb_thread] = serializer_thread_t(thread);
            if (!db_save->threads[dest->nb_thread])
                return false;
            dest->nb_thread++;
        }
    }
    return true;
}

static bool run_fill_channel(
    team_t *team, bin_header_t *dest, database_save_t *db_save)
{
    channel_t *channel = NULL;

    if (team) {
        LIST_FOREACH(channel, &team->channels, entries)
        {
            if (!run_fill_thread(channel, dest, db_save))
                return false;
            db_save->channels[dest->nb_channel] = serializer_channel_t(channel);
            if (!db_save->channels[dest->nb_channel])
                return false;
            dest->nb_channel++;
        }
    }
    return true;
}

bool run_fill_data(
    const database_t *db, bin_header_t *dest, database_save_t *db_save)
{
    team_t *team = NULL;
    user_t *user = NULL;

    LIST_FOREACH(team, &db->teams, entries)
    {
        if (!run_fill_channel(team, dest, db_save))
            return false;
        db_save->teams[dest->nb_team] = serializer_team_t(team);
        if (!db_save->teams[dest->nb_team])
            return false;
        dest->nb_team++;
    }
    LIST_FOREACH(user, &db->users, entries)
    {
        if (!run_fill_private_msg(user, dest, db_save))
            return false;
        db_save->users[dest->nb_user] = serializer_user_t(user);
        if (!db_save->users[dest->nb_user])
            return false;
        dest->nb_user++;
    }
    return true;
}
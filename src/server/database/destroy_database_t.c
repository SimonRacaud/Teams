/*
** EPITECH PROJECT, 2021
** Database
** File description:
** destroy_database_t.c - Created: 19/05/2021
*/

#include "database.h"

void destroy_user_t(user_t *user)
{
    private_msg_t *msg = NULL;
    private_msg_t *last_msg = NULL;

    if (user == NULL)
        return;
    LIST_FOREACH(msg, &user->messages, entries)
    {
        if (last_msg)
            LIST_REMOVE(last_msg, entries);
        free_zero(last_msg, sizeof(private_msg_t));
        last_msg = msg;
    }
    if (last_msg)
        LIST_REMOVE(last_msg, entries);
    free_zero(last_msg, sizeof(private_msg_t));

    LIST_REMOVE(user, entries);
    free_zero(user, sizeof(user_t));
}

void destroy_thread_t(thread_t *thread)
{
    reply_t *reply = NULL;
    reply_t *last_reply = NULL;

    if (thread == NULL)
        return;
    LIST_FOREACH(reply, &thread->replies, entries)
    {
        if (last_reply)
            LIST_REMOVE(last_reply, entries);
        free_zero(last_reply, sizeof(reply_t));
        last_reply = reply;
    }
    if (last_reply)
        LIST_REMOVE(last_reply, entries);
    free_zero(last_reply, sizeof(reply_t));

    LIST_REMOVE(thread, entries);
    free_zero(thread, sizeof(thread_t));
}

static inline void destroy_all_threads(channel_t *channel)
{
    thread_t *thread = NULL;
    thread_t *last_thread = NULL;

    LIST_FOREACH(thread, &channel->threads, entries)
    {
        destroy_thread_t(last_thread);
        last_thread = thread;
    }
    destroy_thread_t(last_thread);
}

void destroy_team_t(team_t *team)
{
    channel_t *channel = NULL;
    channel_t *last_channel = NULL;

    if (team == NULL)
        return;
    LIST_FOREACH(channel, &team->channels, entries)
    {
        destroy_all_threads(channel);
        free_zero(last_channel, sizeof(channel_t));
        last_channel = channel;
    }
    free_zero(last_channel, sizeof(channel_t));
    free_zero(team, sizeof(team_t));
}

void destroy_database_t(database_t *db)
{
    user_t *user = NULL;
    user_t *last_user = NULL;
    team_t *team = NULL;
    team_t *last_team = NULL;

    LIST_FOREACH(user, &db->users, entries)
    {
        destroy_user_t(last_user);
        last_user = user;
    }
    destroy_user_t(last_user);

    LIST_FOREACH(team, &db->teams, entries)
    {
        destroy_team_t(last_team);
        last_team = team;
    }
    destroy_team_t(last_team);

    bzero(db, sizeof(database_t));
}
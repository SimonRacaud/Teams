/*
** EPITECH PROJECT, 2021
** serializer_header_t.c
** File description:
** serializer_bin_header_t function
*/

#include "database.h"
#include "save/bin_header_t.h"

static void run_private_msg(user_t *user, bin_header_t *dest)
{
    private_msg_t *msg = NULL;

    if (user) {
        LIST_FOREACH(msg, &user->messages, entries) {
            dest->nb_private_msg++;
        }
    }
}

static void run_reply(thread_t *thread, bin_header_t *dest)
{
    reply_t *reply = NULL;

    if (thread) {
        LIST_FOREACH(reply, &thread->replies, entries) {
            dest->nb_reply++;
        }
    }
}

static void run_thread(channel_t *channel, bin_header_t *dest)
{
    thread_t *thread = NULL;

    if (channel) {
        LIST_FOREACH(thread, &channel->threads, entries) {
            dest->nb_thread++;
            run_reply(thread, dest);
        }
    }
}

static void run_channel(team_t *team, bin_header_t *dest)
{
    channel_t *channel = NULL;

    if (team) {
        LIST_FOREACH(channel, &team->channels, entries) {
            dest->nb_channel++;
            run_thread(channel, dest);
        }
    }
}

void fill_data_length(const database_t *db, bin_header_t *dest)
{
    team_t *team = NULL;
    user_t *user = NULL;

    if (db) {
        LIST_FOREACH(team, &db->teams, entries) {
            dest->nb_team++;
            run_channel(team, dest);
        }
        LIST_FOREACH(user, &db->users, entries) {
            dest->nb_user++;
            run_private_msg(user, dest);
        }
    }
}
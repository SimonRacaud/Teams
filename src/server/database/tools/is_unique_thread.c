/*
** EPITECH PROJECT, 2021
** is_unique_thread.c
** File description:
** is_unique_thread function
*/

#include "database.h"

static bool running_channel(team_t *node, const char *title)
{
    channel_t *channel = NULL;
    thread_t *thread = NULL;

    LIST_FOREACH(channel, &node->channels, entries) {
        LIST_FOREACH(thread, &channel->threads, entries) {
            if (strcmp(title, thread->title) == 0) {
                return false;
            }
        }
    }
    return true;
}

bool is_unique_thread(database_t *db, const char *title)
{
    team_t *node = NULL;

    LIST_FOREACH(node, &db->teams, entries) {
        if (!running_channel(node, title))
            return false;
    }
    return true;
}
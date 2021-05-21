/*
** EPITECH PROJECT, 2021
** create_reply.c
** File description:
** create_reply function
*/

#include "database.h"

static thread_t *get_thread_from_uuid(
    database_t *db, uuid_selector_t *params, int *err)
{
    thread_t *thread = NULL;
    channel_t *channel = get_channel_from_uuid(db, params, err);

    if (!channel)
        return NULL;
    LIST_FOREACH(thread, &channel->threads, entries)
    {
        if (!uuid_compare(thread->uuid, params->uuid_thread))
            return thread;
    }
    return NULL;
}

static void event(uuid_t thread, uuid_t user, const char *body)
{
    char uuid_thread[UUID_STR];
    char uuid_user[UUID_STR];

    uuid_unparse(thread, uuid_thread);
    uuid_unparse(user, uuid_user);
    server_event_reply_created(uuid_thread, uuid_user, body);
}

static int init_replay_node(
    thread_t *thread, user_t *user, const char *body, uuid_selector_t *params)
{
    reply_t *reply = malloc(sizeof(reply_t));

    if (!reply)
        return ERROR;
    memset(reply, 0, sizeof(reply_t));
    memcpy(reply->body, body, strlen(body));
    reply->timestamp = time(NULL);
    reply->user = user;
    reply->parent_thread = thread;
    uuid_generate(reply->uuid);
    LIST_INSERT_HEAD(&thread->replies, reply, entries);
    uuid_copy(params->uuid_reply, reply->uuid);
    event(thread->uuid, user->uuid, body);
    return SUCCESS;
}

rcode_e create_reply(
    database_t *db, user_t *sender, const char *body, uuid_selector_t *params)
{
    int err = ERROR;
    thread_t *thread = NULL;

    if (!db || !body || !params)
        return ERROR;
    if (strlen(body) > SIZE_BODY)
        return ERROR;
    if (uuid_is_null(params->uuid_team) || uuid_is_null(params->uuid_channel)
        || uuid_is_null(params->uuid_thread))
        return ERROR;
    thread = get_thread_from_uuid(db, params, &err);
    if (!thread)
        return err;
    return init_replay_node(thread, sender, body, params);
}
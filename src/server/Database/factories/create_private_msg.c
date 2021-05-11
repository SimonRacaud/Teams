/*
** EPITECH PROJECT, 2021
** create_private_msg.c
** File description:
** create_private_msg function
*/

#include "database.h"

static user_t *get_user_from_uuid(database_t *db, uuid_t uuid)
{
    user_t *node = NULL;

    LIST_FOREACH(node, &db->users, entries) {
        if (!uuid_compare(node->uuid, uuid))
            return node;
    }
    return NULL;
}

static int init_msg_node(database_t *db,
const char *msg, user_t *sender, uuid_selector_t *params)
{
    user_t *receiver = get_user_from_uuid(db, params->uuid_user);
    private_msg_t *node = malloc(sizeof(private_msg_t));

    if (!node)
        return ERROR;
    if (!receiver) {
        free(node);
        return ERR_UNKNOWN_USER;
    }
    memset(node, 0, sizeof(private_msg_t));
    memcpy(node->body, msg, strlen(msg));
    uuid_generate(node->uuid);
    node->timestamp = time(NULL);
    node->receiver = receiver;
    node->sender = sender;
    return SUCCESS;
}

int create_private_msg(database_t *db,
const char *msg, user_t *sender, uuid_selector_t *params)
{
    int err_val = ERROR;

    if (!db || !msg || !params)
        return ERROR;
    if (strlen(msg) > SIZE_BODY)
        return ERROR;
    if (uuid_is_null(params->uuid_user))
        return ERROR;
    return init_msg_node(db, msg, sender, params);
}
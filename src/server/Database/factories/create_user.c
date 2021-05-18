/*
** EPITECH PROJECT, 2021
** create_user.c
** File description:
** create_user function
*/

#include "database.h"

static bool already_exist(database_t *db, const char *username)
{
    user_t *node = NULL;

    LIST_FOREACH(node, &db->users, entries) {
        if (!strcmp(node->username, username))
            return true;
    }
    return false;
}

static void init_user_node(user_t *node, const char *username)
{
    memset(node, 0, sizeof(user_t));
    memcpy(node->username, username, strlen(username));
    node->status = DISCONNECTED;
    uuid_generate(node->uuid);
}

rcode_e create_user(database_t *db,
const char *username, uuid_selector_t *params)
{
    user_t *node = NULL;

    if (!db || !username)
        return ERROR;
    if (strlen(username) > SIZE_NAME)
        return ERROR;
    if (already_exist(db, username))
        return ERR_ALREADY_EXIST;
    node = malloc(sizeof(user_t));
    if (!node)
        return ERROR;
    init_user_node(node, username);
    LIST_INSERT_HEAD(&db->users, node, entries);
    uuid_copy(params->uuid_user, node->uuid);
    return SUCCESS;
}
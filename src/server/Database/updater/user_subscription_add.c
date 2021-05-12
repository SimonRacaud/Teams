/*
** EPITECH PROJECT, 2021
** get_private_msg.c
** File description:
** get_private_msg function
*/

#include "database.h"

int user_subscription_add(database_t *db, uuid_selector_t *params)
{
    if (!db || !params)
        return ERROR;
    if (uuid_is_null(params->uuid_user) || uuid_is_null(params->uuid_team))
        return ERROR;
    return SUCCESS;
}
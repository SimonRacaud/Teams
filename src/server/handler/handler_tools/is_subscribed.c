/*
** EPITECH PROJECT, 2021
** is_subscribed.c
** File description:
** is_subscribed function
*/

#include "server.h"
#include "utility.h"
#include "database.h"
#include "request_handler_t.h"

bool is_subscribed(client_t *client, uuid_t uuid_team)
{
    team_t *team = NULL;

    LIST_FOREACH(team, &client->user_ptr->teams, entries) {
        if (uuid_compare(team->uuid, uuid_team) == 0)
            return true;
    }
    return false;
}
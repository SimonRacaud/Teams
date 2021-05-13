/*
** EPITECH PROJECT, 2021
** serializer_user_t.c
** File description:
** serializer_user_t function
*/

#include <stdlib.h>
#include <string.h>
#include "data/user_t.h"
#include "save/bin_user_t.h"

static size_t get_teams_length(const user_t *src)
{
    size_t i = 0;
    team_t *node = NULL;

    LIST_FOREACH(node, &src->teams, entries) {
        i++;
    }
    return i;
}

bin_user_t *serializer_user_t(const user_t *src)
{
    bin_user_t *dest = NULL;

    if (!src)
        return NULL;
    dest = malloc(sizeof(bin_user_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(bin_user_t));
    uuid_copy(dest->uuid, src->uuid);
    dest->status = src->status;
    memcpy(dest->name, src->username, strlen(src->username));
    dest->nb_subscribed_teams = get_teams_length(src);
    return dest;
}
/*
** EPITECH PROJECT, 2021
** deserializer_team_t.c
** File description:
** deserializer_team_t function
*/

#include <stdlib.h>
#include <string.h>
#include "data/team_t.h"
#include "data/database_t.h"
#include "save/bin_team_t.h"

team_t *deserializer_team_t(const bin_team_t *src, const database_t *db)
{
    team_t *dest = NULL;

    if (!src || !db)
        return NULL;
    dest = malloc(sizeof(team_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(team_t));
    uuid_copy(dest->uuid, src->uuid);
    memcpy(dest->name, src->name, strlen(src->name));
    memcpy(dest->description, src->description, strlen(src->description));
    return dest;
}
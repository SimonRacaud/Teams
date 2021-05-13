/*
** EPITECH PROJECT, 2021
** serializer_team_t.c
** File description:
** serializer_team_t function
*/

#include <stdlib.h>
#include <string.h>
#include "data/team_t.h"
#include "save/bin_team_t.h"

bin_team_t *serializer_team_t(const team_t *src)
{
    bin_team_t *dest = NULL;

    if (!src)
        return NULL;
    dest = malloc(sizeof(bin_team_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(bin_team_t));
    uuid_copy(dest->uuid, src->uuid);
    memcpy(dest->name, src->name, strlen(src->name));
    memcpy(dest->description, src->description, strlen(src->description));
    return dest;
}
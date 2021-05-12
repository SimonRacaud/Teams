/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 12/05/2021 bin_team_t.h
*/

#ifndef BIN_TEAM_T_H
#define BIN_TEAM_T_H

#include "env.h"
#include <uuid/uuid.h>

typedef struct bin_team_s {
    uuid_t uuid;
    char name[SIZE_NAME];
    char description[SIZE_DESC];
} bin_team_t;

#endif // BIN_TEAM_T_H

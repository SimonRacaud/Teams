/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 12/05/2021 bin_channel_t.h
*/

#ifndef BIN_CHANNEL_T_H
#define BIN_CHANNEL_T_H

#include "env.h"
#include <uuid.h>

typedef struct bin_channel_s {
    uuid_t uuid;
    uuid_t team_uuid;
    char name[SIZE_NAME];
    char description[SIZE_DESC];
} bin_channel_t;

#endif // BIN_CHANNEL_T_H

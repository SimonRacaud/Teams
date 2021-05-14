/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 team_t.h
*/

#ifndef TEAM_T_H
#define TEAM_T_H

#include <sys/queue.h>
#include "uuid.h"
#include "env.h"
#include "user_t.h"
#include "channel_t.h"

typedef struct team_list_header team_list_t;
typedef struct db_team_list_header db_team_list_t;

typedef struct team_s {
    uuid_t uuid;
    char name[SIZE_NAME];
    char description[SIZE_DESC];
    LIST_HEAD(channel_list_header, channel_s) channels;
    LIST_HEAD(user_list_header, user_s) users;
    LIST_ENTRY(team_s) entries;
} team_t;

#endif // TEAM_T_H

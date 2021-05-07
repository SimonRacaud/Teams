/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 database_t.h
*/

#ifndef DATABASE_T_H
#define DATABASE_T_H

#include <sys/queue.h>
#include "user_t.h"
#include "team_t.h"

typedef struct database_s {
    LIST_HEAD(db_user_list_header, user_s) users;
    LIST_HEAD(db_team_list_header, team_s) teams;
} database_t;

#endif // DATABASE_T_H

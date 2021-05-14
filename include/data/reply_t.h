/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 reply_t.h
*/

#ifndef REPLY_T_H
#define REPLY_T_H

#include "uuid.h"
#include "env.h"
#include <time.h>
#include "user_t.h"

typedef struct reply_list_header reply_list_t;

typedef struct reply_s {
    uuid_t uuid;
    user_t *user;
    time_t timestamp;
    char body[SIZE_BODY];
    LIST_ENTRY(reply_s) entries;
} reply_t;

#endif // REPLY_T_H

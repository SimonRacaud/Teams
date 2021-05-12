/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 12/05/2021 bin_reply_t.h
*/

#ifndef BIN_REPLY_T_H
#define BIN_REPLY_T_H

#include <time.h>
#include <uuid.h>
#include "env.h"

typedef struct bin_reply_s {
    uuid_t uuid;
    uuid_t thread_uuid;
    uuid_t user_uuid;
    time_t timestamp;
    char body[SIZE_BODY];
} bin_reply_t;

#endif // BIN_REPLY_T_H

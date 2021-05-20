/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 20/05/2021 bin_reply_event_t.h
*/

#ifndef BIN_REPLY_EVENT_T_H
#define BIN_REPLY_EVENT_T_H

#include "env.h"
#include "uuid.h"

typedef struct bin_reply_event_s {
    uuid_t team;
    uuid_t thread;
    uuid_t user;
    char body[SIZE_BODY];
} bin_reply_event_t;

#endif // BIN_REPLY_EVENT_T_H

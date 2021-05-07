/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 thread_t.h
*/

#ifndef THREAD_T_H
#define THREAD_T_H

#include <sys/queue.h>
#include <time.h>
#include <uuid/uuid.h>
#include "env.h"
#include "user_t.h"
#include "reply_t.h"

typedef struct thread_list_header thread_list_t;

typedef struct thread_s {
    uuid_t uuid;
    char title[SIZE_NAME];
    char body[SIZE_BODY];
    time_t timestamp;
    user_t *user;
    LIST_HEAD(reply_list_header, reply_s) replies;
} thread_t;

#endif // THREAD_T_H

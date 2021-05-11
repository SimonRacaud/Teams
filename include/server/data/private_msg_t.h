/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 private_msg_t.h
*/

#ifndef PRIVATE_MSG_T_H
#define PRIVATE_MSG_T_H

#include "env.h"
#include "user_t.h"
#include <time.h>
#include <uuid.h>

typedef struct private_msg_list_header pm_list_t;

typedef struct user_s user_t;

typedef struct private_msg_s {
    uuid_t uuid;
    user_t *receiver;
    user_t *sender;
    time_t timestamp;
    char body[SIZE_BODY];
    LIST_ENTRY(private_msg_s) entries;
} private_msg_t;

#endif // PRIVATE_MSG_T_H

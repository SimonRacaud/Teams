/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 user_t.h
*/

#ifndef USER_T_H
#define USER_T_H

#include "uuid.h"
#include <sys/queue.h>
#include "env.h"
#include "team_t.h"
#include "private_msg_t.h"

typedef struct user_list_header user_list_t;
typedef struct db_user_list_header db_user_list_t;

typedef enum user_status
{
    CONNECTED = 1,
    DISCONNECTED = 0
} user_status_e;

typedef struct user_s {
    uuid_t uuid;
    user_status_e status;
    char username[SIZE_NAME];
    LIST_HEAD(team_list_header, team_ptr_s) teams;
    LIST_HEAD(pm_list_header, private_msg_s) messages;
    LIST_ENTRY(user_s) entries;
} user_t;

typedef struct user_ptr_s {
    user_t *ptr;
    LIST_ENTRY(user_ptr_s) entries;
} user_ptr_t;

#endif // USER_T_H
/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 12/05/2021 database_save_t.h
*/

#ifndef DATABASE_SAVE_T_H
#define DATABASE_SAVE_T_H

#include "uuid.h"
#include "bin_channel_t.h"
#include "bin_header_t.h"
#include "bin_team_t.h"
#include "bin_thread_t.h"
#include "bin_user_t.h"
#include "bin_private_msg_t.h"
#include "bin_reply_t.h"

typedef struct database_save_s {
    bin_header_t *head;
    bin_user_t **users;
    uuid_t **user_teams_list;
    bin_team_t **teams;
    bin_channel_t **channels;
    bin_thread_t **threads;
    bin_reply_t **replies;
    bin_private_msg_t **messages;
} database_save_t;

#endif // DATABASE_SAVE_T_H

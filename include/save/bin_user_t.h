/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 12/05/2021 bin_user_t.h
*/

#ifndef BIN_USER_T_H
#define BIN_USER_T_H

#include "data/user_t.h"
#include "env.h"

typedef struct bin_user_s {
    uuid_t uuid;
    user_status_e status;
    char name[SIZE_NAME];
    uint nb_subscribed_teams;
} bin_user_t;

#endif // BIN_USER_T_H

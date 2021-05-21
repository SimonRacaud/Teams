/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 20/05/2021 bin_subscription_t.h
*/

#ifndef BIN_SUBSCRIPTION_T_H
#define BIN_SUBSCRIPTION_T_H

#include "uuid.h"
#include "env.h"

typedef struct bin_subscription_s {
    uuid_t user;
    uuid_t team;
} bin_subscription_t;

#endif // BIN_SUBSCRIPTION_T_H

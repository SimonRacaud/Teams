/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 12/05/2021 bin_thread_t.h
*/

#ifndef BIN_THREAD_T_H
#define BIN_THREAD_T_H

#include "data/thread_t.h"

typedef struct bin_thread_s {
    uuid_t uuid;
    uuid_t channel_uuid;
    uuid_t user_uuid;
    time_t timestamp;
    char title[SIZE_NAME];
    char body[SIZE_BODY];
} bin_thread_t;

#endif // BIN_THREAD_T_H

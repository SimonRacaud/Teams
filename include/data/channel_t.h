/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 channel_t.h
*/

#ifndef CHANNEL_T_H
#define CHANNEL_T_H

#include "uuid.h"
#include <sys/queue.h>
#include "env.h"

typedef struct channel_list_header channel_list_t;

typedef struct channel_s {
    uuid_t uuid;
    char name[SIZE_NAME];
    char description[SIZE_DESC];
    LIST_HEAD(thread_list_header, thread_s) threads;
    LIST_ENTRY(channel_s) entries;
} channel_t;

#endif // CHANNEL_T_H

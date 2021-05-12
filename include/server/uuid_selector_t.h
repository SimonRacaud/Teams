/*
** EPITECH PROJECT, 2021
** My TEAMS
** File description:
** uuid_selector_t.h
*/

#ifndef UUID_SELECTOR_T_H_
#define UUID_SELECTOR_T_H_

#include <uuid/uuid.h>

typedef struct uuid_selector_s
{
    uuid_t uuid_user;
    uuid_t uuid_team;
    uuid_t uuid_reply;
    uuid_t uuid_thread;
    uuid_t uuid_channel;
    uuid_t uuid_private_msg;
} uuid_selector_t;

#endif
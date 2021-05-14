/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 12/05/2021 bin_private_msg.h
*/

#ifndef BIN_PRIVATE_MSG_T_H
#define BIN_PRIVATE_MSG_T_H

#include <time.h>
#include "uuid.h"
#include "env.h"

typedef struct bin_private_msg_s {
    uuid_t uuid;
    uuid_t receiver_uuid;
    uuid_t sender_uuid;
    time_t timestamp;
    char body[SIZE_BODY];
} bin_private_msg_t;

#endif // BIN_PRIVATE_MSG_T_H

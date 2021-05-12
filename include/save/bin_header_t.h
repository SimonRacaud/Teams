/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 12/05/2021 bin_header_t.h
*/

#ifndef BIN_HEADER_T_H
#define BIN_HEADER_T_H

#include <stdlib.h>

typedef struct bin_header_s {
    uint nb_user;
    uint nb_team;
    uint nb_channel;
    uint nb_thread;
    uint nb_reply;
    uint nb_private_msg;
} bin_header_t;

#endif // BIN_HEADER_T_H

/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 19/05/2021 logger.h
*/

#ifndef LOGGER_H
#define LOGGER_H

#include "network.h"

#define PRT_SINGLE(cmd)                                 \
    (!strcmp(cmd, CMD_CREATE) || !strcmp(cmd, CMD_INFO) \
        || !strcmp(cmd, CMD_USER))

typedef struct body_handler_s {
    const char *label;
    void (*handler)(response_t *response);
} body_handler_t;

int logger(response_t *response);

void log_string(response_t *response);
void log_logging(response_t *response);
void log_event_team(response_t *response);
void log_event_reply(response_t *response);
void log_event_thread(response_t *response);
void log_event_channel(response_t *response);
void log_print_user(response_t *response);
void log_print_team(response_t *response);
void log_print_channel(response_t *response);
void log_print_thread(response_t *response);
void log_print_reply(response_t *response);
void log_print_private_msg(response_t *response);
void log_error(response_t *response);
void log_subscription(response_t *response);

#endif // LOGGER_H

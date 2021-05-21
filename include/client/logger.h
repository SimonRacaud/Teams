/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 19/05/2021 logger.h
*/

#ifndef LOGGER_H
#define LOGGER_H

#include "network.h"

typedef struct body_handler_s {
    const char *label;
    void (* handler)(response_t *response);
} body_handler_t;

#define LOG_T_STRING "string"
#define LOG_T_LOGGING "logging"
#define LOG_T_EVT_TEAM "event_team"
#define LOG_T_EVT_REPLY "event_reply"
#define LOG_T_EVT_CHAN "event_channel"
#define LOG_T_EVT_THREAD "event_thread"
#define LOG_T_PRT_USER "print_user"
#define LOG_T_PRT_TEAM "print_team"
#define LOG_T_PRT_CHAN "print_channel"
#define LOG_T_PRT_THREAD "print_thread"
#define LOG_T_PRT_REPLY "print_reply"
#define LOG_T_PRT_PRIV_MSG "print_private_msg"
#define LOG_T_ERROR "error"
#define LOG_T_SUBSCRIPTION "subscription"

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

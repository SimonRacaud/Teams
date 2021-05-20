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

int logger(response_t *response);

void log_string(response_t *response);

#endif // LOGGER_H

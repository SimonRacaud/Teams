/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 logger.c
*/

#include "client.h"
#include "logging_client.h"
#include "logger.h"

static const body_handler_t HANDLERS[] = {
    {.label = "string", .handler = &log_string},
    {.label = "logging", .handler = &log_logging},
    {.label = "event_team", .handler = &log_event_team},
    {.label = "event_reply", .handler = &log_event_reply},
    {.label = "event_channel", .handler = &log_event_channel},
    {.label = "event_thread", .handler = &log_event_thread},
    {.label = "print_user", .handler = &log_print_user},
    {.label = "print_team", .handler = &log_print_team},
    {.label = "print_channel", .handler = &log_print_channel},
    {.label = "print_thread", .handler = &log_print_thread},
    {.label = "print_reply", .handler = &log_print_reply},
    {.label = "print_private_msg", .handler = &log_print_private_msg},
    {.label = "error", .handler = &log_error},
    {.label = "subscription", .handler = &log_subscription},
    {.label = NULL, .handler = NULL}
};

static void call_handler(response_t *response)
{
    for (size_t i = 0; HANDLERS[i].label; i++) {
        if (!strcmp(HANDLERS[i].label, response->header->logger)
            && HANDLERS[i].handler) {
            HANDLERS[i].handler(response);
            return;
        }
    }
    printf("WARNING: logger, no handler found %s\n", response->header->logger);
}

int logger(response_t *response)
{
    debug_response(response);
    call_handler(response);
    return EXIT_SUCCESS;
}
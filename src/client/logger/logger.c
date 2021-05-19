/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 logger.c
*/

#include "client.h"
#include "logging_client.h"

static const body_handler_t HANDLERS[] = {
    {.label = "string", .handler = &log_string},
    {.label = "logging", .handler = NULL},
    {.label = "event_team", .handler = NULL},
    {.label = "event_reply", .handler = NULL},
    {.label = "event_channel", .handler = NULL},
    {.label = "event_thread", .handler = NULL},
    {.label = "print_user", .handler = NULL},
    {.label = "print_team", .handler = NULL},
    {.label = "print_channel", .handler = NULL},
    {.label = "print_thread", .handler = NULL},
    {.label = "print_reply", .handler = NULL},
    {.label = "print_private_msg", .handler = NULL},
    {.label = "error", .handler = NULL},
    {.label = "subscription", .handler = NULL},
    {.label = NULL, .handler = NULL}
};

static void call_handler(response_t *response)
{
    for (size_t i = 0; HANDLERS[i].label; i++) {
        if (!strcmp(HANDLERS[i].label, response->header->type)
            && HANDLERS[i].handler) {
            HANDLERS[i].handler(response);
            return;
        }
    }
    printf("WARNING: logger, no handler found %s\n", response->header->type);
}

int logger(response_t *response)
{
    debug_response(response);
    call_handler(response);
    return EXIT_SUCCESS;
}
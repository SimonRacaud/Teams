/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 logger.c
*/

#include "client.h"
#include "logging_client.h"

int logger(response_t *response)
{
    debug_response(response);
    return EXIT_SUCCESS;
}
/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 response_destroy.c
*/

#include "network/response_t.h"
#include <stdlib.h>

void response_destroy(response_t *response)
{
    if (response->req_label) {
        free(response->req_label);
    }
    if (response->req_args) {
        for (size_t i = 0; response->req_args[i] != NULL; i++) {
            free(response->req_args[i]);
        }
        free(response->req_args);
    }
    if (response->body) {
        free(response->body);
    }
}
/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 11/05/2021 request_destroy.c
*/

#include <stdlib.h>
#include "network/request_t.h"

void request_destroy(request_t *request)
{
    if (!request)
        return;
    if (request->label) {
        free(request->label);
    }
    if (request->args) {
        for (size_t i = 0; request->args[i] != NULL; i++) {
            free(request->args[i]);
        }
        free(request->args);
    }
    free(request);
}
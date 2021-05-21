/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 19/05/2021 log_string.c
*/

#include "network.h"

void log_string(response_t *response)
{
    size_t size = response->header->elem_size * response->header->list_size;
    char *content = (char *)response->body;

    if (size > 0) {
        printf("Response: \n%s\n", content);
    }
}
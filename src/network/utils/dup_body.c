/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 22/05/2021 dup_body.c
*/

#include "network.h"

void *dup_body(void *body)
{
    body_header_t *head = body;
    size_t size = head->elem_size * head->list_size;
    void *result = NULL;

    result = malloc(sizeof(body_header_t) + size);
    if (!result)
        return NULL;
    memcpy(result, body, (sizeof(body_header_t) + size));
    return result;
}
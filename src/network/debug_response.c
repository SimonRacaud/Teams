/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 18/05/2021 debug_response.c
*/

#include "network.h"

void debug_response(response_t *response)
{
    size_t size = 0;

    printf("RESPONSE RECEIVED [Label: %s]\n", response->req_label);
    for (size_t i = 0; response->req_args && response->req_args[i]; i++) {
        printf("\tARG %lu : [%s]\n", i, response->req_args[i]);
    }
    printf("\tBODY Type: %s, Element size: %u, List size: %u\n",
        response->header->type, response->header->elem_size,
        response->header->list_size);
    size = response->header->elem_size * response->header->list_size;
    if (!strcmp(response->header->type, "string")) {
        printf("\tContent: \n");
        printf("---------------\n");
        printf("%s\n", (size > 0) ? (char *)response->body : "(empty)");
        printf("---------------\n");
    }
}
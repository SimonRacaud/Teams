/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 18/05/2021 body_maker_string.c
*/

#include "database.h"
#include "server.h"
#include "network/response_t.h"

void *body_maker_string(const char *str)
{
    size_t len = strlen(str);
    void *body = NULL;
    char *content;

    body = malloc(sizeof(body_header_t) + (len + 1));
    if (!body)
        return NULL;
    *((body_header_t *) body) = (body_header_t){
        .elem_size = 1, .list_size = (len + 1), .type = "string"};
    content = (body + sizeof(body_header_t));
    strcpy(content, str);
    return body;
}
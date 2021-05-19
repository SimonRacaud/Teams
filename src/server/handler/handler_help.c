/*
** EPITECH PROJECT, 2021
** handler_help.c
** File description:
** handler_help function
*/

#include "server.h"
#include "request_handler_t.h"

extern const request_handler_t HANDLERS[];

static char *get_help_msg(void)
{
    size_t pos = 0;
    size_t size = 0;
    char *list = NULL;

    for (size_t i = 0; HANDLERS[i].label; i++)
        size += (strlen(HANDLERS[i].label) + 3);
    list = malloc(sizeof(char) * size);
    if (!list)
        return NULL;
    for (size_t u = 0; HANDLERS[u].label; u++) {
        strcpy(list + pos, "- ");
        strcpy(list + pos + 2, HANDLERS[u].label);
        pos += (strlen(HANDLERS[u].label) + 2);
        list[pos++] = (HANDLERS[u + 1].label) ? '\n' : '\0';
    }
    return list;
}

int handler_help(server_t *srv, request_t *request, UNUSED client_t *client)
{
    char *content = NULL;

    if (!srv || !request)
        return EXIT_FAILURE;
    content = get_help_msg();
    if (!content)
        return EXIT_FAILURE;
    return reply_str(SUCCESS, request, content);
}
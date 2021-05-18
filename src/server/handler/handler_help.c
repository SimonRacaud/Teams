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

static void *get_body(void)
{
    body_header_t body_struct = {0};
    const char type[] = "string";
    char *msg = get_help_msg();
    void *body = NULL;

    if (!msg)
        return NULL;
    body = malloc(sizeof(body_header_t) + strlen(msg));
    if (!body)
        return NULL;
    body_struct.list_size = 1;
    body_struct.elem_size = strlen(msg);
    memcpy(body_struct.type, type, strlen(type));
    memcpy(body, &body_struct, sizeof(body_header_t));
    memcpy(body + sizeof(body_header_t), msg, body_struct.elem_size);
    free(msg);
    return body;
}

int handler_help(server_t *srv, request_t *request)
{
    response_t *response = NULL;
    int return_value = 0;
    void *body = NULL;

    if (!srv || !request)
        return EXIT_FAILURE;
    body = get_body();
    if (!body)
        return EXIT_FAILURE;
    response = response_create(SUCCESS, request, request->receiver, body);
    if (!response)
        return EXIT_FAILURE;
    return_value = response_send(response);
    response_destroy(response);
    return return_value;
}
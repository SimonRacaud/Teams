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
    for (size_t i = 0; HANDLERS[i].label; i++) {
        strcpy(list + pos, "- ");
        strcpy(list + pos + 2, HANDLERS[i].label);
        pos += (strlen(HANDLERS[i].label) + 2 + 1);
        list[pos++] = (HANDLERS[i + 1].label) ? '\n' : '\0';
    }
    return list;
}

static char *generate_tram(int enum_stat,
const char *field, size_t *length, const char **arg)
{
    size_t len = 3 + strlen(field) + sizeof(uint);
    size_t len_tmp = 0;
    uint nb_arg = get_tab_len(arg);
    char embedded = '\0';
    char *tram = malloc(len);

    if (!tram)
        return NULL;
    sprintf(tram, "%.2i%c%s", enum_stat, embedded, field);
    tram[3 + strlen(field) + 1] = nb_arg;
    for (size_t i = 0; i < nb_arg; i++) {
        len_tmp = strlen(arg[i]) + 1;
        tram = realloc(tram, len + len_tmp);
        if (!tram)
            return NULL;
        memcpy(tram + len, arg[i], len_tmp);
        len += len_tmp;
    }
    *length = len;
    return tram;
}

static char *add_body(char *tram, size_t *length)
{
    body_header_t body = {0};
    const char type[] = "string";
    char *msg = get_help_msg();

    if (!msg)
        return NULL;
    body.list_size = 1;
    body.elem_size = strlen(msg);
    memcpy(body.type, type, strlen(type));
    tram = realloc(tram, *length + sizeof(body_header_t) + body.elem_size);
    if (!tram)
        return NULL;
    memcpy(tram + (*length), &body, sizeof(body_header_t));
    *length += sizeof(body_header_t);
    memcpy(tram + (*length), msg, body.elem_size);
    *length += body.elem_size;
    free(msg);
    return tram;
}

static char *generate_response(request_t *request)
{
    const char **params = (const char **) request->args;
    size_t length = 0;
    char *tram = NULL;

    tram = generate_tram(SUCCESS, request->label, &length, params);
    if (!tram)
        return NULL;
    tram = add_body(tram, &length);
    if (!tram)
        return NULL;
    return add_crlf(tram, length);
}

int handler_help(server_t *srv, request_t *request)
{
    char *msg = NULL;
    int return_value = 0;

    if (!srv || !request)
        return EXIT_FAILURE;
    msg = generate_response(request);
    if (!msg)
        return EXIT_FAILURE;
    return_value = socket_send(request->receiver, msg);
    free(msg);
    return return_value;
}
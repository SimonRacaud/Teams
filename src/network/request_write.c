/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 11/05/2021 write_request.c
*/

#include "env.h"
#include "utility.h"
#include "network/request_t.h"

const char *REQ_FIELD_END = "\r\r";

char *strconcat_suffix(char *str, const char *add, const char *suffix)
{
    char *res = strconcat(str, add);

    if (!res)
        return NULL;
    return strconcat(res, suffix);
}

int request_write(request_t *request)
{
    int fd;
    char *str = NULL;

    if (!request || !request->label || !request->receiver)
        return EXIT_FAILURE;
    fd = request->receiver->fd;
    str = strconcat_suffix(str, request->label, REQ_FIELD_END);
    for (size_t i = 0; request->args && request->args[i] != NULL; i++) {
        str = strconcat_suffix(str, request->args[i], REQ_FIELD_END);
    }
    str = strconcat(str, END_COM);
    write(fd, str, strlen(str));
    free(str);
    return EXIT_SUCCESS;
}

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

static char *add_str(char *str, const char *add)
{
    char *res = strconcat(str, add);

    return strconcat(res, REQ_FIELD_END);
}

int request_write(request_t *request)
{
    int fd;
    char *str = NULL;

    if (!request || !request->label || !request->receiver)
        return EXIT_FAILURE;
    fd = request->receiver->fd;
    str = add_str(str, request->label);
    for (size_t i = 0; request->args && request->args[i] != NULL; i++) {
        str = add_str(str, request->args[i]);
    }
    str = add_str(str, END_COM);
    write(fd, str, strlen(str));
    free(str);
    return EXIT_SUCCESS;
}

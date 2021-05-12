/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 11/05/2021 write_request.c
*/

#include "utility.h"
#include "network/request_t.h"
#include "env.h"

int request_write(request_t *request)
{
    int fd;

    if (!request || !request->label || !request->receiver)
        return EXIT_FAILURE;
    fd = request->receiver->fd;
    if (write(fd, request->label, strlen(request->label) + 1) == -1)
        return EXIT_FAILURE;
    if (request->args) {
        for (size_t i = 0; request->args[i] != NULL; i++) {
            write(fd, request->args[i], strlen(request->args[i]) + 1);
        }
    }
    if (write(fd, END_COM, strlen(END_COM)) == -1)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 app_select.c
*/

#include <sys/select.h>
#include "server.h"

static void get_read_fds(client_list_t *list, int server_fd, fd_set *read_fds)
{
    client_t *ptr;

    FD_ZERO(read_fds);
    FD_SET(server_fd, read_fds);
    LIST_FOREACH(ptr, list, entries)
    {
        FD_SET(ptr->socket.fd, read_fds);
    }
}

static void get_write_fds(response_stack_t *stack, fd_set *write_fds)
{
    response_t *ptr;

    FD_ZERO(write_fds);
    SLIST_FOREACH(ptr, stack, entries)
    {
        FD_SET(ptr->receiver->fd, write_fds);
    }
}

int app_select(server_t *server)
{
    get_read_fds(
        &server->clients, server->socket.fd, &server->select.read_fds);
    get_write_fds(&server->responses, &server->select.write_fds);
    if (select(FD_SETSIZE, &server->select.read_fds, &server->select.write_fds,
            NULL, NULL)
        == -1) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
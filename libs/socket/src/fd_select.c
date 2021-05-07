/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myftp-simon.racaud
** File description:
** 15/04/2021 socket_server_select.c
*/

#include <stdarg.h>
#include "socket.h"

static void init_fds(fd_set *fds, int *fd_array, size_t size)
{
    FD_ZERO(fds);
    for (size_t i = 0; i < size; i++) {
        FD_SET(fd_array[i], fds);
    }
}

int fd_select(select_t *data, size_t size_read, size_t size_write, int *fds)
{
    fd_set *write_fds_ptr = NULL;

    init_fds(&data->read_fds, fds, size_read);
    if (size_write > 0) {
        init_fds(&data->write_fds, (fds + size_read), size_write);
        write_fds_ptr = &data->write_fds;
    }
    data->status =
        select(FD_SETSIZE, &data->read_fds, write_fds_ptr, NULL, NULL);
    if (data->status == -1) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
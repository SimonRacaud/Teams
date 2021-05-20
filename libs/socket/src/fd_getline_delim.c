/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 04/05/2021 fd_getline2.c
*/

#include "socket.h"

static const size_t READ_SIZE = 42;

static int allocator(buffer_t *buffer, size_t inc)
{
    if (!buffer->buff) {
        buffer->buff = malloc(sizeof(char) * (inc + 1));
        if (!buffer->buff)
            return EXIT_FAILURE;
        buffer->buff[0] = '\0';
        buffer->size = (inc + 1);
        buffer->data_size = 0;
    } else {
        if (buffer->size - buffer->data_size > inc) {
            return EXIT_SUCCESS;
        }
        buffer->size += inc;
        buffer->buff = realloc(buffer->buff, sizeof(char) * buffer->size);
        if (!buffer->buff)
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static int read_line(int fd, buffer_t *buffer, const char *delim, bool *empty)
{
    char *delim_ptr = GET_DELIM(buffer->buff, delim);
    ssize_t read_len = READ_SIZE;

    while (!delim_ptr && (size_t) read_len == READ_SIZE) {
        read_len = read(fd, &buffer->buff[buffer->data_size], READ_SIZE);
        if (read_len == -1) {
            perror("read");
            return EXIT_FAILURE;
        } else if (read_len == 0 && empty) {
            *empty = true;
        }
        buffer->buff[buffer->data_size + read_len] = '\0';
        buffer->data_size += read_len;
        delim_ptr = GET_DELIM(buffer->buff, delim);
        if (!delim_ptr && allocator(buffer, READ_SIZE))
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static char *process_result(buffer_t *buffer, const char *delim)
{
    char *delim_ptr = GET_DELIM(buffer->buff, delim);
    size_t delim_size = strlen(delim);
    char *line;

    if (!delim_ptr) {
        return NULL;
    } else if (buffer->data_size - ((delim_ptr + delim_size) - buffer->buff)
        > 0) {
        *delim_ptr = '\0';
        line = strndup(buffer->buff, (delim_ptr - buffer->buff));
        buffer->data_size -= (strlen(line) + delim_size);
        memcpy(buffer->buff, (delim_ptr + delim_size), buffer->data_size + 1);
    } else {
        *delim_ptr = '\0';
        line = buffer->buff;
        buffer->buff = NULL;
        buffer->data_size = 0;
    }
    return line;
}

char *fd_getline_delim(
    int fd, buffer_t *buffer, const char *delim, bool *empty)
{
    if (allocator(buffer, READ_SIZE))
        return NULL;
    if (read_line(fd, buffer, delim, empty))
        return NULL;
    return process_result(buffer, delim);
}
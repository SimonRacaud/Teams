/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 04/05/2021 fd_getline2.c
*/

#include "socket.h"

static const size_t READ_SIZE = 42;

static char *allocator(char *previous, size_t inc)
{
    size_t size;
    char *res;

    if (!previous) {
        res = malloc(sizeof(char) * inc);
        res[0] = '\0';
        return res;
    } else {
        size = strlen(previous) + 1;
        return realloc(previous, sizeof(char) * (inc + size));
    }
}

static char *read_line(int fd, char *buffer, const char *delim, bool *empty)
{
    char *delim_ptr = GET_DELIM(buffer, delim);
    ssize_t read_len = READ_SIZE;
    size_t end = strlen(buffer);

    while (!delim_ptr && (size_t) read_len == READ_SIZE) {
        read_len = read(fd, &buffer[end], READ_SIZE);
        if (read_len == -1) {
            perror("read");
            return NULL;
        } else if (read_len == 0 && empty) {
            *empty = true;
        }
        buffer[end + read_len] = '\0';
        end += read_len;
        delim_ptr = strstr(buffer, delim);
        if (!delim_ptr)
            buffer = allocator(buffer, READ_SIZE);
    }
    return buffer;
}

char *fd_getline_delim(
    int fd, char **buffer_ptr, const char *delim, bool *empty)
{
    char *buffer = allocator(*buffer_ptr, READ_SIZE);
    char *delim_ptr;
    size_t delim_size = strlen(delim);

    buffer = read_line(fd, buffer, delim, empty);
    if (!buffer)
        return NULL;
    delim_ptr = GET_DELIM(buffer, delim);
    if (!delim_ptr) {
        *buffer_ptr = buffer;
        return NULL;
    } else if (strlen(delim_ptr + delim_size) > 0) {
        *buffer_ptr = strdup(delim_ptr + delim_size);
    } else {
        *buffer_ptr = NULL;
    }
    *delim_ptr = '\0';
    return buffer;
}
/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 04/05/2021 fd_getline2.c
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

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

static char *read_line(int fd, char *buffer)
{
    char *new_line_ptr = strchr(buffer, '\n');
    ssize_t read_len = READ_SIZE;
    size_t end = strlen(buffer);

    while (!new_line_ptr && (size_t)read_len == READ_SIZE) {
        read_len = read(fd, &buffer[end], READ_SIZE);
        if (read_len == -1) {
            perror("read");
            return NULL;
        }
        buffer[end + read_len] = '\0';
        end += read_len;
        new_line_ptr = strchr(buffer, '\n');
        if (!new_line_ptr)
            buffer = allocator(buffer, READ_SIZE);
    }
    return buffer;
}

char *fd_getline(int fd, char **buffer_ptr)
{
    char *buffer = allocator(*buffer_ptr, READ_SIZE);
    char *new_line_ptr;

    buffer = read_line(fd, buffer);
    if (!buffer)
        return NULL;
    new_line_ptr = strchr(buffer, '\n');
    if (!new_line_ptr) {
        *buffer_ptr = buffer;
        return NULL;
    } else if (strlen(new_line_ptr + 1) > 0) {
        *buffer_ptr = strdup(new_line_ptr + 1);
    }
    *new_line_ptr = '\0';
    return buffer;
}
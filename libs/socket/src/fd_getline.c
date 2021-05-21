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
#include <stdbool.h>
#include <ctype.h>

static const size_t READ_SIZE = 42;

static bool is_empty(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isgraph(str[i]) && !isblank(str[i])) {
            return false;
        }
    }
    return true;
}

static char *allocator(char *previous, size_t inc)
{
    size_t size;
    char *res;

    if (!previous) {
        res = malloc(sizeof(char) * (inc + 1));
        res[0] = '\0';
        return res;
    } else {
        size = strlen(previous) + 1;
        return realloc(previous, sizeof(char) * (inc + size));
    }
}

static char *read_line(int fd, char *buffer, bool *empty)
{
    char *new_line_ptr = strchr(buffer, '\n');
    ssize_t read_len = READ_SIZE;
    size_t end = strlen(buffer);

    *empty = false;
    while (!new_line_ptr && (size_t)read_len == READ_SIZE) {
        read_len = read(fd, &buffer[end], READ_SIZE);
        if (read_len == -1) {
            perror("read");
            return NULL;
        } else if (read_len == 0) {
            *empty = true;
        }
        buffer[end + read_len] = '\0';
        end += read_len;
        new_line_ptr = strchr(buffer, '\n');
        if (!new_line_ptr)
            buffer = allocator(buffer, READ_SIZE);
    }
    return buffer;
}

char *fd_getline(int fd, char **buffer_ptr, bool *empty)
{
    char *buffer = allocator(*buffer_ptr, READ_SIZE);
    char *new_line_ptr;

    buffer = read_line(fd, buffer, empty);
    if (!buffer)
        return NULL;
    new_line_ptr = strchr(buffer, '\n');
    if (!new_line_ptr) {
        *buffer_ptr = buffer;
        return NULL;
    } else if (is_empty(new_line_ptr + 1) == false) {
        *new_line_ptr = '\0';
        *buffer_ptr = strdup(new_line_ptr + 1);
    } else {
        *buffer_ptr = NULL;
    }
    *new_line_ptr = '\0';
    return buffer;
}
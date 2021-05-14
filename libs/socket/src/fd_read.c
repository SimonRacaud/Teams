/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 04/05/2021 fd_getline2.c
*/

#include "socket.h"

static void init_buffer(char **buffer_ptr, char *buffer, size_t size)
{
    strncpy(buffer, *buffer_ptr, size);
    if (strlen(*buffer_ptr) > size) {
        strcpy(*buffer_ptr, &(*buffer_ptr)[size]);
    } else {
        free(*buffer_ptr);
        *buffer_ptr = NULL;
    }
}

char *fd_read(int fd, char **buffer_ptr, size_t size)
{
    char *buffer = malloc(sizeof(char) * (size + 1));
    size_t content_len = !(*buffer_ptr) ? 0 : strlen(*buffer_ptr);
    ssize_t len = 0;

    if (!buffer)
        return NULL;
    buffer[0] = '\0';
    buffer[size] = '\0';
    if (*buffer_ptr) {
        init_buffer(buffer_ptr, buffer, size);
    }
    if (content_len < size) {
        len = read(fd, &buffer[content_len], (size - content_len));
        if (len == -1 || content_len + len != size) {
            free(buffer);
            return NULL;
        }
    }
    return buffer;
}
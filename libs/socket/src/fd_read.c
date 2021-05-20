/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 04/05/2021 fd_getline2.c
*/

#include "socket.h"

static char *init_buffer(buffer_t *buffer, char *result, size_t size)
{
    size_t copy_size = buffer->data_size;

    if (copy_size > size)
        copy_size = size;
    memcpy(result, buffer->buff, copy_size);
    if (buffer->data_size > size) {
        buffer->data_size -= copy_size;
        memcpy(buffer->buff, &buffer->buff[copy_size], buffer->data_size);
    } else {
        free(buffer->buff);
        buffer->buff = NULL;
        buffer->data_size = 0;
    }
    return result;
}

char *fd_read(int fd, buffer_t *buffer, size_t size)
{
    char *result = malloc(size);
    size_t content_len = !buffer->buff ? 0 : buffer->data_size;
    ssize_t len = 0;

    if (!result)
        return NULL;
    if (buffer->buff) {
        result = init_buffer(buffer, result, size);
    }
    if (content_len < size) {
        len = read(fd, &result[content_len], (size - content_len));
        if (len == -1 || content_len + len != size) {
            free(result);
            return NULL;
        }
    }
    return result;
}
/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myftp-simon.racaud
** File description:
** 15/04/2021 socket_receive.c
*/

#include "socket.h"
#include "utility.h"

static const size_t BUFF_SIZE = 42;

static char *alloc_line(char *line, size_t *buffer_len, size_t line_len)
{
    char *new = NULL;

    if (!line) {
        *buffer_len += (BUFF_SIZE + 1);
        return calloc(1, sizeof(char) * (BUFF_SIZE + 1));
    } else {
        if (line_len + BUFF_SIZE < *buffer_len) {
            return line;
        }
        new = realloc(line, (*buffer_len) + BUFF_SIZE);
        *buffer_len += BUFF_SIZE;
    }
    return new;
}

char *get_line(int fd, char *line, size_t *line_len, size_t *buffer_len)
{
    ssize_t read_len = 1;
    ssize_t new_line_idx = find_newline(line);

    while (line && new_line_idx == -1 && read_len != 0) {
        read_len = read(fd, &line[*line_len], BUFF_SIZE);
        if (read_len == -1) {
            perror("read");
            return NULL;
        }
        (*line_len) += read_len;
        line[*line_len] = '\0';
        new_line_idx = find_newline(line);
        if (new_line_idx == -1)
            line = alloc_line(line, buffer_len, (*line_len));
    }
    return line;
}

static void update_buffer(char **buffer_ptr, char *line, ssize_t eof_idx)
{
    if (eof_idx != -1) {
        line = &line[eof_idx + 1];
    }
    if (!is_empty(line)) {
        *buffer_ptr = strdup(line);
    } else {
        *buffer_ptr = NULL;
    }
}

static char *format_and_check_line(char *line, ssize_t new_line_idx)
{
    if (new_line_idx != -1) {
        if (new_line_idx > 0 && line[new_line_idx - 1] == '\r')
            line[new_line_idx - 1] = '\0';
        else
            line[new_line_idx] = '\0';
    } else {
        free(line);
        return NULL;
    }
    return line;
}

char *socket_getline(socket_t *sock, char **buffer_ptr, bool *empty)
{
    size_t line_len = (!(*buffer_ptr)) ? 0 : strlen(*buffer_ptr);
    size_t buffer_len = 0;
    char *line = alloc_line((*buffer_ptr), &buffer_len, line_len);
    ssize_t new_line_idx;

    if (!line)
        return NULL;
    line = get_line(sock->fd, line, &line_len, &buffer_len);
    if (!line)
        return NULL;
    new_line_idx = find_newline(line);
    update_buffer(buffer_ptr, line, new_line_idx);
    line = format_and_check_line(line, new_line_idx);
    if (line_len == 0)
        *empty = true;
    #ifdef DEBUG
    fprintf(stderr, "line: (%s)\n", line ? line : "null");
    fprintf(stderr, "received: %lu bytes\n", line_len);
    #endif
    return line;
}
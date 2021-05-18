/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 response_parse.c
*/

#include "network.h"
#include "utility.h"

extern const char *FIELD_END;

static int free_all(buffer_t *buffer, char *ptr, response_t *response)
{
    free(ptr);
    free(buffer->buff);
    free(response);
    return EXIT_FAILURE;
}

static int read_header_req_arguments(
    response_t *response, int fd, buffer_t *buffer)
{
    char *ptr = NULL;
    uint size = 0;

    if (!(ptr = fd_getline_delim(fd, buffer, FIELD_END, NULL)))
        return free_all(buffer, ptr, response);
    size = atoi(ptr);
    free(ptr);
    if (size > 0) {
        if (!(response->req_args = malloc(sizeof(char *) * (size + 1))))
            return EXIT_FAILURE;
        response->req_args[size] = NULL;
    } else {
        response->req_args = NULL;
    }
    for (size_t i = 0; i < (size_t) size; i++) {
        if (!(ptr = fd_getline_delim(fd, buffer, FIELD_END, NULL)))
            return free_all(buffer, ptr, response);
        response->req_args[i] = ptr;
    }
    return EXIT_SUCCESS;
}

static int read_header(response_t *response, int fd, buffer_t *buffer)
{
    char *ptr = NULL;

    response->receiver = NULL;
    if (!(ptr = fd_getline_delim(fd, buffer, FIELD_END, NULL))) {
        return free_all(buffer, ptr, response);
    } else if (strlen(ptr) != 3 && is_number(ptr) == false) {
        return free_all(buffer, ptr, response);
    }
    response->err_code = atoi(ptr);
    if (!(ptr = fd_getline_delim(fd, buffer, FIELD_END, NULL))) {
        return free_all(buffer, ptr, response);
    }
    response->req_label = ptr;
    if (read_header_req_arguments(response, fd, buffer))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

static int read_body(response_t *response, int fd, buffer_t *buffer)
{
    size_t size = 0;

    response->header =
        (body_header_t *) fd_read(fd, buffer, sizeof(body_header_t));
    if (!response->header)
        return EXIT_FAILURE;
    size = response->header->elem_size * response->header->list_size;
    if (size == 0) {
        free(response->header);
        return EXIT_SUCCESS;
    }
    if (!(response->body = fd_read(fd, buffer, size))) {
        free(response->header);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

response_t *response_read(int fd, buffer_t *buffer)
{
    response_t *response = malloc(sizeof(response_t));

    if (!response)
        return NULL;
    response->body = NULL;
    if (read_header(response, fd, buffer) == EXIT_FAILURE)
        return NULL;
    if (read_body(response, fd, buffer) == EXIT_FAILURE) {
        free(buffer->buff);
        buffer->buff = NULL;
        return NULL;
    }
    return response;
}
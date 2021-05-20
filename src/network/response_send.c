/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 response_send.c
*/

#include <unistd.h>
#include "network.h"

const char *FIELD_END = "\n\n";

static void send_response_with_body(response_t *response, int fd, char *buffer)
{
    const body_header_t empty_header = {0, 0, "", ""};
    size_t buffer_len = strlen(buffer);
    char *response_buffer = NULL;
    body_header_t *header = NULL;
    size_t body_size = 0;

    if (response->body) {
        header = (body_header_t *) response->body;
        body_size =
            header->elem_size * header->list_size + sizeof(body_header_t);
        response_buffer = realloc(buffer, buffer_len + body_size);
        memcpy(&response_buffer[buffer_len], response->body, body_size);
    } else {
        body_size = sizeof(body_header_t);
        response_buffer = realloc(buffer, buffer_len + body_size);
        memcpy(&response_buffer[buffer_len], &empty_header, body_size);
    }
    write(fd, response_buffer, body_size + buffer_len);
    free(response_buffer);
}

static char *set_request_fields(response_t *response, char *buffer)
{
    uint arg_size = 0;
    char size_str[3] = "00";

    buffer = strconcat_suffix(buffer, response->req_label, FIELD_END);
    while (response->req_args && response->req_args[arg_size]) {
        arg_size++;
    }
    if (sprintf(size_str, "%02u", arg_size) == -1) {
        strcpy(size_str, "00");
    }
    buffer = strconcat_suffix(buffer, size_str, FIELD_END);
    for (size_t i = 0; response->req_args && response->req_args[i]; i++) {
        buffer = strconcat_suffix(buffer, response->req_args[i], FIELD_END);
    }
    return buffer;
}

int response_send(response_t *response)
{
    int fd = (response->receiver) ? response->receiver->fd : -1;
    char code[4] = "000";
    char *buffer = NULL;

    if (!response->receiver)
        return EXIT_FAILURE;
    if (sprintf(code, "%03u", (uint) response->err_code) == -1)
        return EXIT_FAILURE;
    buffer = strconcat_suffix(NULL, code, FIELD_END);
    buffer = set_request_fields(response, buffer);
    if (!buffer)
        return EXIT_FAILURE;
    send_response_with_body(response, fd, buffer);
    return EXIT_SUCCESS;
}

/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 response_send.c
*/

#include "network.h"
#include <unistd.h>

static const char *RESPONSE_END = "\r\n";
const char *FIELD_END = "\n\n";
size_t FIELD_END_SIZE = 2;

static void write_field(int fd, const char *str)
{
    write(fd, str, strlen(str));
    write(fd, FIELD_END, FIELD_END_SIZE);
}

static void send_body(response_t *response, int fd)
{
    size_t size = 0;
    body_header_t *header = NULL;
    const body_header_t empty_header = {0, 0, ""};

    if (response->body) {
        header = (body_header_t *)response->body;
        size = header->elem_size * header->list_size + sizeof(body_header_t);
        write(fd, response->body, size);
    } else {
        write(fd, &empty_header, sizeof(body_header_t));
    }
}

static void send_request(response_t *response, int fd)
{
    uint arg_size = 0;
    char buffer[3] = "00";

    write_field(fd, response->req_label);
    while (response->req_args && response->req_args[arg_size]) {
        arg_size++;
    }
    if (sprintf(buffer, "%02u", arg_size) == -1) {
        strcpy(buffer, "00");
    }
    write_field(fd, buffer);
    for (size_t i = 0; response->req_args && response->req_args[i]; i++) {
        write_field(fd, response->req_args[i]);
    }
}

int response_send(response_t *response)
{
    int fd = (response->receiver) ? response->receiver->fd : -1;
    char buffer[4] = "000";

    if (!response->receiver)
        return EXIT_FAILURE;
    if (sprintf(buffer, "%03u", (uint)response->err_code) == -1)
        return EXIT_FAILURE;
    write_field(fd, buffer);
    send_request(response, fd);
    send_body(response, fd);
    write(fd, RESPONSE_END, strlen(RESPONSE_END));
    return EXIT_SUCCESS;
}

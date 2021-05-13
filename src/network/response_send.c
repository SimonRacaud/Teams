/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 response_send.c
*/

#include "network.h"
#include <unistd.h>

static const char *RESPONSE_END = "\r\n";

static void send_body(response_t *response, int fd)
{
    size_t size = 0;
    body_header_t *header = (body_header_t *)response->body;

    size = header->elem_size * header->list_size + sizeof(body_header_t);
    write(fd, response->body, size);
}

static void send_request(response_t *response, int fd)
{
    uint arg_size = 0;

    write(fd, response->req_label, strlen(response->req_label) + 1);
    while (response->req_args && response->req_args[arg_size]) {
        arg_size++;
    }
    write(fd, &arg_size, sizeof(uint));
    for (size_t i = 0; response->req_args && response->req_args[i]; i++) {
        write(fd, response->req_args[i], strlen(response->req_args[i]) + 1);
    }
}

int response_send(response_t *response)
{
    int fd = (response->receiver) ? response->receiver->fd : -1;
    char buffer[4] = "000";

    if (!response->receiver)
        return EXIT_FAILURE;
    if (sscanf(buffer, "%03u", (uint *)&response->err_code) == -1)
        return EXIT_FAILURE;
    write(fd, buffer, 4);
    send_request(response, fd);
    if (response->body) {
        send_body(response, fd);
    }
    write(fd, RESPONSE_END, strlen(RESPONSE_END));
    return EXIT_SUCCESS;
}

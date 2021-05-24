/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 21/05/2021 log_print_reply.c
*/

#include "env.h"
#include "network.h"
#include "logging_client.h"

static bool handle_creator(response_t *response, bin_reply_t *data)
{
    char thread_uuid[UUID_STR];
    char user_uuid[UUID_STR];

    if (!strcmp(response->req_label, CMD_CREATE)) {
        uuid_unparse(data->thread_uuid, thread_uuid);
        uuid_unparse(data->user_uuid, user_uuid);
        client_print_reply_created(
            thread_uuid, user_uuid, data->timestamp, data->body);
        return true;
    }
    return false;
}

static void handle_printer(response_t *response, bin_reply_t *data)
{
    char thread_uuid[UUID_STR];
    char user_uuid[UUID_STR];

    for (size_t i = 0; i < response->header->list_size; i++) {
        uuid_unparse(data[i].thread_uuid, thread_uuid);
        uuid_unparse(data[i].user_uuid, user_uuid);
        client_thread_print_replies(
            thread_uuid, user_uuid, data[i].timestamp, data[i].body);
    }
}

void log_print_reply(response_t *response)
{
    size_t size = response->header->elem_size * response->header->list_size;
    bin_reply_t *data = (bin_reply_t *) response->body;

    if (size == 0)
        return;
    if (size < sizeof(bin_reply_t) || (size % sizeof(bin_reply_t)) != 0) {
        printf("Warning: logger - bad size\n");
        return;
    }
    if (handle_creator(response, data)) {
        return;
    }
    handle_printer(response, data);
}

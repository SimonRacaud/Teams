/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 21/05/2021 log_print_thread.c
*/

#include "env.h"
#include "network.h"
#include "logging_client.h"
#include "logger.h"

static bool handle_creator(response_t *response, bin_thread_t *data)
{
    char thread_uuid[UUID_STR];
    char user_uuid[UUID_STR];

    if (!strcmp(response->req_label, CMD_CREATE)) {
        uuid_unparse(data->uuid, thread_uuid);
        uuid_unparse(data->user_uuid, user_uuid);
        client_print_thread_created(
            thread_uuid, user_uuid, data->timestamp, data->title, data->body);
        return true;
    }
    return false;
}

static void handle_printer(response_t *response, bin_thread_t *data)
{
    char thread_uuid[UUID_STR];
    char user_uuid[UUID_STR];

    if (PRT_SINGLE(response->req_label)) {
        uuid_unparse(data->uuid, thread_uuid);
        uuid_unparse(data->user_uuid, user_uuid);
        client_print_thread(
            thread_uuid, user_uuid, data->timestamp, data->title, data->body);
    } else {
        for (size_t i = 0; i < response->header->list_size; i++) {
            uuid_unparse(data[i].uuid, thread_uuid);
            uuid_unparse(data[i].user_uuid, user_uuid);
            client_channel_print_threads(thread_uuid, user_uuid,
                data[i].timestamp, data[i].title, data[i].body);
        }
    }
}

void log_print_thread(response_t *response)
{
    size_t size = response->header->elem_size * response->header->list_size;
    bin_thread_t *data = (bin_thread_t *) response->body;

    if (size == 0)
        return;
    if (size < sizeof(bin_thread_t) || (size % sizeof(bin_thread_t)) != 0) {
        printf("Warning: logger - bad size\n");
        return;
    }
    if (handle_creator(response, data)) {
        return;
    }
    handle_printer(response, data);
}

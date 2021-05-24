/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 21/05/2021 log_print_channel.c
*/

#include "env.h"
#include "network.h"
#include "logging_client.h"

static bool handle_creator(response_t *response, bin_channel_t *data)
{
    char channel_uuid[UUID_STR];

    if (!strcmp(response->req_label, CMD_CREATE)) {
        uuid_unparse(data->uuid, channel_uuid);
        client_print_channel_created(
            channel_uuid, data->name, data->description);
        return true;
    }
    return false;
}

static void handler_print(response_t *response, bin_channel_t *data)
{
    char channel_uuid[UUID_STR];

    for (size_t i = 0; i < response->header->list_size; i++) {
        uuid_unparse(data[i].uuid, channel_uuid);
        if (response->header->list_size == 1) {
            client_print_channel(
                channel_uuid, data[i].name, data->description);
        } else {
            client_team_print_channels(
                channel_uuid, data[i].name, data->description);
        }
    }
}

void log_print_channel(response_t *response)
{
    size_t size = response->header->elem_size * response->header->list_size;
    bin_channel_t *data = (bin_channel_t *) response->body;

    if (size == 0)
        return;
    if (size < sizeof(bin_channel_t) || (size % sizeof(bin_channel_t)) != 0) {
        printf("Warning: logger - bad size\n");
        return;
    }
    if (handle_creator(response, data)) {
        return;
    }
    handler_print(response, data);
}

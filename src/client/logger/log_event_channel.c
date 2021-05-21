/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 21/05/2021 log_event_channel.c
*/

#include "env.h"
#include "network.h"
#include "logging_client.h"

void log_event_channel(response_t *response)
{
    size_t size = response->header->elem_size * response->header->list_size;
    bin_channel_t *data = (bin_channel_t *) response->body;
    char channel_uuid[UUID_STR];

    if (size != sizeof(bin_channel_t)) {
        printf("Warning: logger - bad size\n");
        return;
    }
    uuid_unparse(data->uuid, channel_uuid);
    client_event_channel_created(channel_uuid, data->name, data->description);
}

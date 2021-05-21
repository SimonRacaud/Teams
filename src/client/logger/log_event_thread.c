/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 21/05/2021 log_event_thread.c
*/

#include "env.h"
#include "network.h"
#include "logging_client.h"

void log_event_thread(response_t *response)
{
    size_t size = response->header->elem_size * response->header->list_size;
    bin_thread_t *data = (bin_thread_t *) response->body;
    char thread_uuid[UUID_STR];
    char user_uuid[UUID_STR];

    if (size != sizeof(bin_thread_t)) {
        printf("Warning: logger - bad size\n");
        return;
    }
    uuid_unparse(data->uuid, thread_uuid);
    uuid_unparse(data->user_uuid, user_uuid);
    client_event_thread_created(
        thread_uuid, user_uuid, data->timestamp, data->title, data->body);
}

/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 21/05/2021 log_event_reply.c
*/

#include "env.h"
#include "network.h"
#include "logging_client.h"
#include "save/bin_reply_event_t.h"

void log_event_reply(response_t *response)
{
    size_t size = response->header->elem_size * response->header->list_size;
    bin_reply_event_t *data = (bin_reply_event_t *) response->body;
    char team_uuid[UUID_STR];
    char thread_uuid[UUID_STR];
    char user_uuid[UUID_STR];

    if (size != sizeof(bin_reply_event_t)) {
        printf("Warning: logger - bad size\n");
        return;
    }
    uuid_unparse(data->team, team_uuid);
    uuid_unparse(data->thread, thread_uuid);
    uuid_unparse(data->user, user_uuid);
    client_event_thread_reply_received(
        team_uuid, thread_uuid, user_uuid, data->body);
}

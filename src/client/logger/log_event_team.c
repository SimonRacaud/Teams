/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 20/05/2021 log_event_team.c
*/

#include "network.h"
#include "logging_client.h"
#include "env.h"

void log_event_team(response_t *response)
{
    size_t size = response->header->elem_size * response->header->list_size;
    bin_team_t *data = (bin_team_t *) response->body;
    char uuid[UUID_STR];

    if (size != sizeof(bin_team_t)) {
        printf("Warning: logger - bad size\n");
        return;
    }
    uuid_unparse(data->uuid, uuid);
    client_event_team_created(uuid, data->name, data->description);
}

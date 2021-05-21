/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 21/05/2021 log_print_team.c
*/

#include "env.h"
#include "network.h"
#include "logging_client.h"

static bool handle_creator(response_t *response, bin_team_t *data)
{
    char team_uuid[UUID_STR];

    if (!strcmp(response->req_label, CMD_CREATE)) {
        uuid_unparse(data->uuid, team_uuid);
        client_print_team_created(
            team_uuid, data->name, data->description);
        return true;
    }
    return false;
}

void log_print_team(response_t *response)
{
    size_t size = response->header->elem_size * response->header->list_size;
    bin_team_t *data = (bin_team_t *) response->body;
    char team_uuid[UUID_STR];

    if (size < sizeof(bin_team_t) || (size % sizeof(bin_team_t)) != 0) {
        printf("Warning: logger - bad size\n");
        return;
    }
    if (handle_creator(response, data))
        return;
    for (size_t i = 0; i < response->header->list_size; i++) {
        uuid_unparse(data[i].uuid, team_uuid);
        if (response->header->list_size == 1) {
            client_print_team(team_uuid, data[i].name, data[i].description);
        } else {
            client_print_teams(team_uuid, data[i].name, data[i].description);
        }
    }
}

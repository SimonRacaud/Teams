/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 19/05/2021 log_team.c
*/

#include "network.h"
#include "logging_client.h"
#include "env.h"

void log_logging(response_t *response)
{
    size_t size = response->header->elem_size * response->header->list_size;
    bin_user_t *data = (bin_user_t *) response->body;
    char user_uuid[UUID_STR];

    if (size != sizeof(bin_user_t)) {
        printf("Warning: logger - bad size\n");
        return;
    }
    uuid_unparse(data->uuid, user_uuid);
    if (!strcmp(response->req_label, "login")) {
        client_event_logged_in(user_uuid, data->name);
    } else if (!strcmp(response->req_label, "logout")) {
        client_event_logged_out(user_uuid, data->name);
    }
}

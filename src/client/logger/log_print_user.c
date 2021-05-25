/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 21/05/2021 log_print_user.c
*/

#include "env.h"
#include "network.h"
#include "logging_client.h"
#include "logger.h"

void log_print_user(response_t *response)
{
    size_t size = response->header->elem_size * response->header->list_size;
    bin_user_t *data = (bin_user_t *) response->body;
    char user_uuid[UUID_STR];

    if (size == 0)
        return;
    if (size < sizeof(bin_user_t) || (size % sizeof(bin_user_t)) != 0) {
        printf("Warning: logger - empty || bad size\n");
        return;
    }
    if (PRT_SINGLE(response->req_label)) {
        uuid_unparse(data->uuid, user_uuid);
        client_print_user(user_uuid, data->name, (int) data->status);
    } else {
        for (size_t i = 0; i < response->header->list_size; i++) {
            uuid_unparse(data[i].uuid, user_uuid);
            client_print_users(user_uuid, data[i].name, (int) data[i].status);
        }
    }
}

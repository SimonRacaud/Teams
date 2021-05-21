/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 21/05/2021 log_print_user.c
*/

#include "env.h"
#include "network.h"
#include "logging_client.h"

void log_print_user(response_t *response)
{
    size_t size = response->header->elem_size * response->header->list_size;
    bin_user_t *data = (bin_user_t *) response->body;
    char user_uuid[UUID_STR];

    if (size < sizeof(bin_user_t) || (size % sizeof(bin_user_t)) != 0) {
        printf("Warning: logger - bad size\n");
        return;
    }
    for (size_t i = 0; i < response->header->list_size; i++) {
        uuid_unparse(data[i].uuid, user_uuid);
        if (response->header->list_size == 1) {
            client_print_user(user_uuid, data[i].name, (int) data[i].status);
        } else {
            client_print_users(user_uuid, data[i].name, (int) data[i].status);
        }
    }
}

/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 21/05/2021 log_subscription.c
*/

#include "network.h"
#include "logging_client.h"
#include "env.h"
#include "save/bin_subscription_t.h"

void log_subscription(response_t *response)
{
    size_t size = response->header->elem_size * response->header->list_size;
    bin_subscription_t *data = (bin_subscription_t *) response->body;
    char uuid_user[UUID_STR];
    char uuid_team[UUID_STR];

    if (size != sizeof(bin_subscription_t)) {
        printf("Warning: logger - bad size\n");
        return;
    }
    uuid_unparse(data->user, uuid_user);
    uuid_unparse(data->team, uuid_team);
    if (!strcmp(response->req_label, CMD_SUBSCRIBE)) {
        client_print_subscribed(uuid_user, uuid_team);
    } else if (!strcmp(response->req_label, CMD_UNSUBSCRIBE)) {
        client_print_unsubscribed(uuid_user, uuid_team);
    }
}

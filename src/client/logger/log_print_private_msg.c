/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 21/05/2021 log_print_private_msg.c
*/

#include "env.h"
#include "network.h"
#include "logging_client.h"

static bool handle_receipt(response_t *response, bin_private_msg_t *data)
{
    char user_uuid[UUID_STR];

    if (!strcmp(response->req_label, CMD_SEND)) {
        uuid_unparse(data->sender_uuid, user_uuid);
        client_event_private_message_received(user_uuid, data->body);
        return true;
    }
    return false;
}

static void handle_printer(response_t *response, bin_private_msg_t *data)
{
    char sender_uuid[UUID_STR];

    for (size_t i = 0; i < response->header->list_size; i++) {
        uuid_unparse(data[i].sender_uuid, sender_uuid);
        client_private_message_print_messages(
            sender_uuid, data[i].timestamp, data[i].body);
    }
}

void log_print_private_msg(response_t *response)
{
    size_t size = response->header->elem_size * response->header->list_size;
    bin_private_msg_t *data = (bin_private_msg_t *) response->body;

    if (size < sizeof(bin_private_msg_t)
        || (size % sizeof(bin_private_msg_t)) != 0) {
        printf("Warning: logger - bad size\n");
        return;
    }
    if (handle_receipt(response, data)) {
        return;
    }
    handle_printer(response, data);
}

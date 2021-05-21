/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 21/05/2021 log_error.c
*/

#include "network.h"
#include "logging_client.h"
#include "env.h"

static void norme_compliant_switch(rcode_e code, char *uuid)
{
    switch (code) {
        case ERR_UNKNOWN_CHANNEL:
            client_error_unknown_channel(uuid);
            break;
        case ERR_UNKNOWN_TEAM:
            client_error_unknown_team(uuid);
            break;
        default:
            printf("Error type response received\n");
    }
}

static void call_function(rcode_e code, char *uuid)
{
    switch (code) {
        case ERR_UNAUTHORISED:
            client_error_unauthorized();
            break;
        case ERR_ALREADY_EXIST:
            client_error_already_exist();
            break;
        case ERR_UNKNOWN_USER:
            client_error_unknown_user(uuid);
            break;
        case ERR_UNKNOWN_THREAD:
            client_error_unknown_thread(uuid);
            break;
        default:
            norme_compliant_switch(code, uuid);
    }
}

void log_error(response_t *response)
{
    size_t size = response->header->elem_size * response->header->list_size;
    uuid_t *data = (uuid_t *) response->body;
    char uuid[UUID_STR];
    rcode_e code = response->err_code;

    if (size != sizeof(uuid_t)) {
        printf("Warning: logger - bad size\n");
        return;
    }
    uuid_unparse((*data), uuid);
    call_function(code, uuid);
}

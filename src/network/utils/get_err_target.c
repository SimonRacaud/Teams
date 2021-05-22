/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 21/05/2021 get_err_target.c
*/

#include "network.h"

static void get_target(uuid_t *dest, rcode_e code, uuid_selector_t *params,
    uuid_t def)
{
    switch (code) {
        case ERR_UNKNOWN_USER:
            uuid_copy(*dest, params->uuid_user);
            break;
        case ERR_UNKNOWN_THREAD:
            uuid_copy(*dest, params->uuid_thread);
            break;
        case ERR_UNKNOWN_CHANNEL:
            uuid_copy(*dest, params->uuid_channel);
            break;
        case ERR_UNKNOWN_TEAM:
            uuid_copy(*dest, params->uuid_team);
            break;
        default:
            uuid_copy(*dest, def);
    }
}

void get_err_target(uuid_t *dest, uuid_selector_t *params, rcode_e code)
{
    uuid_t def = {0};

    if (!dest) {
        return;
    }
    if (!params) {
        uuid_copy(*dest, def);
    }
    get_target(dest, code, params, def);
}
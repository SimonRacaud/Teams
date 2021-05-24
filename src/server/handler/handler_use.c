/*
** EPITECH PROJECT, 2021
** handler_use.c
** File description:
** handler_use function
*/

#include "database.h"
#include "server.h"
#include "utility.h"
#include "request_handler_t.h"

static void *(*const VERIF[]) (const database_t *db,
    uuid_selector_t *params) = {
    (void *(*) (const database_t *, uuid_selector_t *) ) get_team,
    (void *(*) (const database_t *, uuid_selector_t *) ) get_channel,
    (void *(*) (const database_t *, uuid_selector_t *) ) get_thread};

static int selector_verification(size_t args_size, selected_entity_t *selector,
    server_t *server, request_t *request)
{
    const rcode_e err_tab[] = {
        ERR_UNKNOWN_TEAM, ERR_UNKNOWN_CHANNEL, ERR_UNKNOWN_THREAD};
    void *result = NULL;
    uuid_selector_t params = {0};

    uuid_copy(params.uuid_team, selector->team);
    uuid_copy(params.uuid_channel, selector->channel);
    uuid_copy(params.uuid_thread, selector->thread);
    for (size_t i = 0; i < args_size; i++) {
        result = VERIF[i](&server->database, &params);
        if (!result) {
            reply((rerr_t){err_tab[i], &params}, request, NULL, server);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

static int parse_args(
    server_t *srv, selected_entity_t *selector, request_t *request)
{
    size_t i = 0;
    char *move_ptr = (char *)selector;
    const rcode_e err_tab[] = {
        ERR_UNKNOWN_TEAM, ERR_UNKNOWN_CHANNEL, ERR_UNKNOWN_THREAD};

    for (; request->args && request->args[i];
        i++, move_ptr += sizeof(uuid_t)) {
        if (uuid_parse(request->args[i], (unsigned char *) move_ptr) == -1) {
            reply_str(srv, err_tab[i], request, "Invalid argument");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int handler_use(server_t *srv, request_t *request, client_t *client)
{
    selected_entity_t selector = {0};
    size_t nb_arg = walen(request->args);

    if (nb_arg > 3) {
        return reply_str(srv, ERROR, request, "Invalid argument size");
    }
    if (parse_args(srv, &selector, request) == EXIT_FAILURE) {
        return EXIT_SUCCESS;
    }
    if (selector_verification(nb_arg, &selector, srv, request)
        == EXIT_FAILURE) {
        return EXIT_SUCCESS;
    }
    memcpy(&client->selector, &selector, sizeof(selected_entity_t));
    return reply_str(srv, SUCCESS, request, "Use correctly executed");
}
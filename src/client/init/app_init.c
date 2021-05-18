/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 app_init.c
*/

#include <signal.h>
#include "client.h"

static void init_stack(client_t *client)
{
    MY_LIST_HEAD_INITIALIZER(client->stack);
    SLIST_INIT(&client->stack);
}

int app_init(client_t *client, int argc, char **argv)
{
    client->cli_buffer = NULL;
    client->loop = false;
    client->response_buffer.buff = NULL;
    uuid_clear(client->selector.team);
    uuid_clear(client->selector.channel);
    uuid_clear(client->selector.thread);
    init_stack(client);
    if (parse_args(&client->args, argc, argv) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (connect_to_server(&client->socket, client->args.port, client->args.ip))
        return EXIT_FAILURE;
    if (signal_manager(SIGINT, &client->loop) == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
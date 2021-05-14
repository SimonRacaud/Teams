/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 connect_client.c
*/

#include "server.h"

int connect_client(server_t *server)
{
    client_t *client = malloc(sizeof(client_t));

    if (!client)
        return EXIT_FAILURE;
    if (socket_server_connect(&client->socket, server->socket.fd)) {
        free(client);
        return EXIT_FAILURE;
    }
    client->user_ptr = NULL;
    client->read_buffer = NULL;
    LIST_INSERT_HEAD(&server->clients, client, entries);
    return EXIT_SUCCESS;
}

void disconnect_client(client_t *client)
{
    if (client->read_buffer) {
        free(client->read_buffer);
    }
    socket_close(&client->socket);
    LIST_REMOVE(client, entries);
}
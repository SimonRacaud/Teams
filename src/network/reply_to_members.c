/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 22/05/2021 reply_to_members.c
*/

#include "network.h"
#include "database.h"

static void find_socket_and_reply(server_t *server, void *body,
    request_t *request, user_t *target)
{
    client_t *client;
    response_t *response;
    void *res_body = NULL;

    LIST_FOREACH(client, &server->clients, entries) {
        if (client->user_ptr == target) {
            res_body = dup_body(body);
            response =
                response_create(SUCCESS, request, &client->socket, res_body);
            response_push(server, response);
            break;
        }
    }
}

int reply_to_members(
    server_t *server, request_t *request, void *body, uuid_t team_uuid)
{
    uuid_selector_t select = {0};
    team_t *team;
    user_t *user;

    uuid_copy(select.uuid_team, team_uuid);
    team = get_team(&server->database, &select);
    if (!team)
        return EXIT_FAILURE;
    LIST_FOREACH(user, &team->users, entries) {
        find_socket_and_reply(server, body, request, user);
    }
    free(body);
    return EXIT_SUCCESS;
}
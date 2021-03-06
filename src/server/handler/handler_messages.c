/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 19/05/2021 handler_messages.c
*/

#include "database.h"
#include "server.h"
#include "utility.h"
#include "uuid_selector_t.h"

static mp_list_t create_list(user_t *user_alpha, user_t *user_beta)
{
    private_msg_t *ptr = NULL;
    private_msg_t *node = NULL;
    mp_list_t head = LIST_HEAD_INITIALIZER(head);

    LIST_INIT(&head);
    LIST_FOREACH(node, &user_alpha->messages, entries) {
        if (node->sender == user_beta) {
            ptr = private_msg_copy(node);
            LIST_INSERT_HEAD(&head, ptr, entries);
        }
    }
    LIST_FOREACH(node, &user_beta->messages, entries) {
        if (node->sender == user_alpha) {
            ptr = private_msg_copy(node);
            LIST_INSERT_HEAD(&head, ptr, entries);
        }
    }
    return head;
}

static int send_reply(mp_list_t *list, request_t *request, server_t *server)
{
    void *body =
        body_maker_private_msg(LIST_FIRST(list), true, LOG_T_PRT_PRIV_MSG);

    if (!body)
        return EXIT_FAILURE;
    return reply((rerr_t){SUCCESS, NULL}, request, body, server);
}

static int process_response(user_t *user_alpha, user_t *user_beta,
    request_t *request, server_t *server)
{
    mp_list_t head = create_list(user_alpha, user_beta);
    private_msg_t *ptr2 = NULL;
    private_msg_t *ptr = NULL;
    int code = EXIT_SUCCESS;

    if (send_reply(&head, request, server) == EXIT_FAILURE)
        code = EXIT_FAILURE;
    ptr = LIST_FIRST(&head);
    while (ptr != NULL) {
        ptr2 = LIST_NEXT(ptr, entries);
        free(ptr);
        ptr = ptr2;
    }
    return code;
}

int handler_messages(
    server_t *server, request_t *request, UNUSED client_t *client)
{
    user_t *user_alpha = client->user_ptr;
    uuid_selector_t selector = {0};
    user_t *user_beta = NULL;
    char *user_uuid = NULL;

    if (walen(request->args) != 1)
        return reply_str(server, ERROR, request, "Bad argument count");
    if (user_alpha == NULL)
        return reply_error(server, ERR_UNAUTHORISED, request, NULL);
    user_uuid = request->args[0];
    if (uuid_parse(user_uuid, selector.uuid_user) == -1)
        return reply_error(server, ERR_UNKNOWN_USER, request, NULL);
    user_beta = get_user(&server->database, &selector);
    if (!user_beta)
        return reply_error(
            server, ERR_UNKNOWN_USER, request, &selector.uuid_user);
    return process_response(user_alpha, user_beta, request, server);
}
/*
** EPITECH PROJECT, 2021
** handler_send.c
** File description:
** handler_send function
*/

#include "database.h"
#include "env.h"
#include "server.h"
#include "utility.h"
#include "request_handler_t.h"

static void event(private_msg_t *msg)
{
    char sender_uuid[UUID_STR];
    char receiver_uuid[UUID_STR];

    uuid_unparse(msg->receiver->uuid, receiver_uuid);
    uuid_unparse(msg->sender->uuid, sender_uuid);
    server_event_private_message_sended(sender_uuid, receiver_uuid, msg->body);
}

int handler_send(server_t *srv, request_t *req, client_t *client)
{
    uuid_selector_t select = {0};
    int ret_value = SUCCESS;
    private_msg_t *msg;
    void *body;

    if (!srv || !req)
        return EXIT_FAILURE;
    if (walen(req->args) != 2)
        return reply_str(srv, ERROR, req, "Invalid argument count");
    if (uuid_parse(req->args[0], select.uuid_user) == -1)
        return reply_str(srv, ERROR, req, "Invalid argument");
    ret_value = create_private_msg(
        &srv->database, req->args[1], client->user_ptr, &select);
    msg = get_private_msg(&srv->database, &select);
    if (!msg)
        return EXIT_FAILURE;
    event(msg);
    body = body_maker_private_msg(msg, false, LOG_T_PRT_PRIV_MSG);
    return reply(ret_value, req, body, &select);
}
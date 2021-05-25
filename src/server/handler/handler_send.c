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

static int send_message(
    server_t *srv, request_t *req, private_msg_t *msg, user_t *receiver)
{
    void *body;

    body = body_maker_private_msg(msg, false, LOG_T_PRT_PRIV_MSG);
    reply_to_target(srv, req, body, receiver);
    return reply_str(srv, SUCCESS, req, "Message sent");
}

static int send_error(server_t *srv, request_t *req)
{
    return reply_str(srv, ERROR, req, "An error occured");
}

int handler_send(server_t *srv, request_t *req, client_t *client)
{
    uuid_selector_t select = {0};
    rcode_e ret_value = SUCCESS;
    private_msg_t *msg;
    user_t *receiver = NULL;

    if (walen(req->args) != 2)
        return reply_str(srv, ERROR, req, "Invalid argument count");
    if (uuid_parse(req->args[0], select.uuid_user) == -1)
        return reply_error(srv, ERR_UNKNOWN_USER, req, NULL);
    ret_value = create_private_msg(
        &srv->database, req->args[1], client->user_ptr, &select);
    if (ret_value == ERR_UNKNOWN_USER)
        return reply_error(srv, ret_value, req, &select.uuid_user);
    msg = get_private_msg(&srv->database, &select);
    receiver = get_user(&srv->database, &select);
    if (!msg || !receiver)
        return EXIT_FAILURE;
    event(msg);
    return (ret_value == SUCCESS) ? send_message(srv, req, msg, receiver)
                                  : send_error(srv, req);
}
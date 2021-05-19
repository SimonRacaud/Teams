/*
** EPITECH PROJECT, 2021
** handler_send.c
** File description:
** handler_send function
*/

#include "server.h"
#include "utility.h"
#include "database.h"
#include "request_handler_t.h"

int handler_send(server_t *srv, request_t *req, client_t *client)
{
    uuid_selector_t select = {0};
    int ret_value = SUCCESS;

    if (!srv || !req)
        return EXIT_FAILURE;
    if (walen(req->args) != 2)
        return reply_str(ERROR, req, "Invalid argument count");
    if (uuid_parse(req->args[0], select.uuid_user) == -1)
        return reply_str(ERROR, req, "Invalid argument");
    ret_value =
    create_private_msg(&srv->database, req->args[1], client->user_ptr, &select);
    return reply_str(ret_value, req,
    (ret_value) ? "Msg correctly send" : "Echec send msg");
}
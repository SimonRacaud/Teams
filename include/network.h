/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 11/05/2021 network.h
*/

#ifndef NETWORK_H
#define NETWORK_H

#include <stdbool.h>

#include "socket.h"
#include "network/request_t.h"
#include "network/response_t.h"
#include "save/bin_user_t.h"
#include "save/bin_team_t.h"
#include "save/bin_reply_t.h"
#include "save/bin_thread_t.h"
#include "save/bin_channel_t.h"
#include "save/bin_private_msg_t.h"

/// REQUEST
request_t *request_create(char *command);
request_t *request_parse(char *input);
void request_destroy(request_t *request);
int request_write(request_t *request);

/// RESPONSE
response_t *response_create(
    rcode_e code, request_t *request, socket_t *client, void *body);
response_t *response_read(int fd);
void response_destroy(response_t *response);
int response_send(response_t *response);

/// BODY
void *body_maker_team(team_t *team, bool is_list);
void *body_maker_reply(reply_t *reply, bool is_list);
void *body_maker_thread(thread_t *thread, bool is_list);
void *body_maker_user(user_t *user, bool is_list);
void *body_maker_private_msg(private_msg_t *private_msg, bool is_list);
void *body_maker_channel(channel_t *channel, bool is_list);

#endif // NETWORK_H

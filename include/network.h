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
#include "save/bin_channel_t.h"
#include "save/bin_private_msg_t.h"
#include "save/bin_reply_t.h"
#include "save/bin_team_t.h"
#include "save/bin_thread_t.h"
#include "save/bin_user_t.h"
#include "server/uuid_selector_t.h"
#include "server/server_t.h"

typedef struct request_stack_s request_stack_t;

/// REQUEST
request_t *request_create(char *command);
request_t *request_parse(char *input);
void request_destroy(request_t *request);
int request_write(request_t *request);
void request_push(request_stack_t *stack, request_t *req, socket_t *client);

/// RESPONSE
response_t *response_create(
    rcode_e code, request_t *request, socket_t *client, void *body);
void response_destroy(response_t *response);
int response_send(response_t *response);
response_t *response_read(int fd, buffer_t *buffer);

int reply(
    rcode_e code, request_t *request, void *body, uuid_selector_t *params);
int reply_str(rcode_e code, request_t *request, const char *str);
int reply_error(rcode_e code, request_t *request, uuid_t target);
int reply_target(
    server_t *server, request_t *request, void *body, user_t *user);

/// BODY
void *body_maker_team(team_t *team, bool is_list, const char *logger);
void *body_maker_reply(reply_t *reply, bool is_list, const char *logger);
void *body_maker_thread(thread_t *thread, bool is_list, const char *logger);
void *body_maker_user(user_t *user, bool is_list, const char *logger);
void *body_maker_private_msg(
    private_msg_t *private_msg, bool is_list, const char *logger);
void *body_maker_channel(channel_t *channel, bool is_list, const char *logger);
void *body_maker_string(const char *str);
void *body_maker_uuid(uuid_t uuid, const char *logger);
void *body_maker_subscription(uuid_t user, uuid_t team);
void *body_maker_reply_event(reply_t *reply, uuid_t team);

/// COPY
private_msg_t *private_msg_copy(private_msg_t *input);

/// UTILITY
char *strconcat_suffix(char *str, const char *add, const char *suffix);
void get_err_target(uuid_t *dest, uuid_selector_t *params, rcode_e code);
socket_t *get_socket_user(server_t *server, user_t *user);

/// DEBUG
void debug_response(response_t *response);

#endif // NETWORK_H

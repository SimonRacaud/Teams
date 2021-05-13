/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 11/05/2021 parser.h
*/

#ifndef PARSER_H
#define PARSER_H

#include "network/request_t.h"
#include "save/bin_user_t.h"
#include "save/bin_team_t.h"
#include "save/bin_reply_t.h"
#include "save/bin_thread_t.h"
#include "save/bin_channel_t.h"
#include "save/bin_private_msg_t.h"

request_t *request_create(char *command);
int request_write(request_t *request);
void request_destroy(request_t *request);
request_t *request_parse(char *input);

/// BODY
void *body_maker_team(team_t *team, bool is_list);
void *body_maker_reply(reply_t *reply, bool is_list);
void *body_maker_thread(thread_t *thread, bool is_list);
void *body_maker_user(user_t *user, bool is_list);
void *body_maker_private_msg(private_msg_t *private_msg, bool is_list);
void *body_maker_channel(channel_t *channel, bool is_list);

#endif // PARSER_H

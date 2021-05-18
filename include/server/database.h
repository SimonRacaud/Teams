/*
** EPITECH PROJECT, 2021
** My TEAMS
** File description:
** database
*/

#ifndef DATABASE_H_
#define DATABASE_H_

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "client_t.h"
#include "data/thread_t.h"
#include "data/database_t.h"
#include "uuid_selector_t.h"
#include "network/response_t.h"

#include "save/bin_user_t.h"
#include "save/bin_team_t.h"
#include "save/bin_reply_t.h"
#include "save/bin_thread_t.h"
#include "save/bin_header_t.h"
#include "save/bin_channel_t.h"
#include "save/database_save_t.h"
#include "save/bin_private_msg_t.h"

/*
**
** TOOLS
**
*/

size_t get_nb_team_from_user(user_t *user);
void fill_data_length(const database_t *db, bin_header_t *dest);
team_t *get_match_team(const database_t *db, uuid_selector_t *params);
user_t *get_user_from_uuid(const database_t *db, const uuid_t uuid);
channel_t *get_channel_from_uuid(const database_t *db,
uuid_selector_t *params, int *err);
bool run_fill_data(const database_t *db,
    bin_header_t *dest, database_save_t *db_save);

/*
**
** FACTORIES
**
*/

rcode_e create_reply(database_t *db,
user_t *sender, const char *body, uuid_selector_t *params);
rcode_e create_private_msg(database_t *db,
const char *msg, user_t *sender, uuid_selector_t *params);
rcode_e create_team(database_t *db,
const char *teamname, const char *desc, uuid_selector_t *params);
rcode_e create_channel(database_t *db,
const char *channelname, const char *desc, uuid_selector_t *params);
rcode_e create_user(database_t *db,
const char *username, __attribute__((unused)) uuid_selector_t *params);
rcode_e create_thread(database_t *db,
const char *title, const char *msg, uuid_selector_t *params);

/*
**
** GETTER
**
*/

user_t *get_user(const database_t *db, uuid_selector_t *params);
team_t *get_team(const database_t *db, uuid_selector_t *params);
reply_t *get_reply(const database_t *db, uuid_selector_t *params);
thread_t *get_thread(const database_t *db, uuid_selector_t *params);
channel_t *get_channel(const database_t *db, uuid_selector_t *params);
private_msg_t *get_private_msg(const database_t *db, uuid_selector_t *params);

/*
**
** UPDATER
**
*/

int user_subscription_add(database_t *db, uuid_selector_t *params);
int user_subscription_remove(database_t *db, uuid_selector_t *params);

/*
**
** SERIALIZER
**
*/

bin_private_msg_t *serializer_private_msg_t(const private_msg_t *src);
bin_channel_t *serializer_channel_t(const channel_t *src);
bin_header_t *serializer_header_t(const database_t *db);
bin_thread_t *serializer_thread_t(const thread_t *src);
bin_reply_t *serializer_reply_t(const reply_t *src);
bin_team_t *serializer_team_t(const team_t *src);
bin_user_t *serializer_user_t(const user_t *src);

/*
**
** DESERIALIZER
**
*/

user_t *deserializer_user_t(const bin_user_t *src, const database_t *db);
team_t *deserializer_team_t(const bin_team_t *src, const database_t *db);
reply_t *deserializer_reply_t(const bin_reply_t *src, const database_t *db);
thread_t *deserializer_thread_t(const bin_thread_t *src, const database_t *db);
channel_t *deserializer_channel_t(
    const bin_channel_t *src, const database_t *db);
private_msg_t *deserializer_private_msg_t(
    const bin_private_msg_t *src, const database_t *db);

#endif

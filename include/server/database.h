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

/*
**
** FACTORIES
**
*/

int create_reply(database_t *db, const char *msg, uuid_selector_t *params);
int create_team(database_t *db, const char *teamname, uuid_selector_t *params);
int create_private_msg(database_t *db, const char *msg, uuid_selector_t *params);
int create_channel(database_t *db,
const char *channelname, uuid_selector_t *params);
int create_user(database_t *db,
const char *username, __attribute((unused)) uuid_selector_t *params);
int create_thread(database_t *db,
const char *threadname, uuid_selector_t *params);

/*
**
** GETTER
**
*/

user_t *get_user(database_t *db, uuid_selector_t *params);
team_t *get_team(database_t *db, uuid_selector_t *params);
reply_t *get_reply(database_t *db, uuid_selector_t *params);
thread_t *get_thread(database_t *db, uuid_selector_t *params);
channel_t *get_channel(database_t *db, uuid_selector_t *params);
private_msg_t *get_private_msg(database_t *db, uuid_selector_t *params);

/*
**
** UPDATER
**
*/

int user_subscription_add(database_t *db, uuid_selector_t *params);
int user_subscription_remove(database_t *db, uuid_selector_t *params);

#endif

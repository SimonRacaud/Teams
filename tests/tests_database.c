/*
** EPITECH PROJECT, 2021
** tests
** File description:
** tests_database.c - Created: 20/05/2021
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "database.h"

const int nbr_threads_per_channel = 4;
const int nbr_replies_per_thread = 6;

// Test save empty db
Test(save_db, t01)
{
    database_t db;

    create_empty_database(&db);
    cr_assert_eq(save_database(&db), true);
}

static void create_users(database_t *db, const int nbr_users)
{
    char username[SIZE_NAME];
    uuid_selector_t selector;

    bzero(username, SIZE_NAME);
    bzero(&selector, sizeof(uuid_selector_t));
    for (int i = 1; i <= nbr_users; i++) {
        sprintf(username, "U%d", i);
        cr_assert_eq(create_user(db, username, &selector), SUCCESS);
    }
}

static void create_private_messages(database_t *db, const int nbr_private_msg)
{
    user_t *user;
    uuid_selector_t selector;
    char message[SIZE_BODY];

    bzero(message, SIZE_BODY);
    bzero(&selector, sizeof(uuid_selector_t));
    LIST_FOREACH(user, &db->users, entries)
    {
        uuid_copy(selector.uuid_user, LIST_FIRST(&db->users)->uuid);
        for (int n = 1; n <= nbr_private_msg; n++) {
            sprintf(message, "%s M%d", user->username, n);
            cr_assert_eq(
                create_private_msg(db, message, user, &selector), SUCCESS);
        }
    }
}

static void create_teams(database_t *db, const int nbr_teams)
{
    char name[SIZE_NAME];
    char description[SIZE_DESC];
    uuid_selector_t selector;

    bzero(name, SIZE_NAME);
    bzero(description, SIZE_DESC);
    bzero(&selector, sizeof(uuid_selector_t));
    for (int i = 1; i <= nbr_teams; i++) {
        sprintf(name, "T%d", i);
        sprintf(description, "%s description", name);
        cr_assert_eq(create_team(db, name, description, &selector), SUCCESS);
    }
}

static void create_channels(database_t *db, const int nbr_channel_per_team)
{
    team_t *team;
    uuid_selector_t selector;
    char name[SIZE_NAME];
    char description[SIZE_DESC];

    bzero(name, SIZE_NAME);
    bzero(description, SIZE_DESC);
    bzero(&selector, sizeof(uuid_selector_t));
    LIST_FOREACH(team, &db->teams, entries)
    {
        uuid_copy(selector.uuid_team, team->uuid);
        for (int n = 1; n <= nbr_channel_per_team; n++) {
            sprintf(name, "C%d", n);
            sprintf(description, "%s description", name);
            cr_assert_eq(
                create_channel(db, name, description, &selector), SUCCESS);
        }
    }
}

static void create_threads(database_t *db)
{
    team_t *team;
    channel_t *channel;
    uuid_selector_t params;
    char title[SIZE_NAME];
    char msg[SIZE_BODY];

    bzero(title, SIZE_NAME);
    bzero(msg, SIZE_BODY);
    bzero(&params, sizeof(uuid_selector_t));
    uuid_copy(params.uuid_user, LIST_FIRST(&db->users)->uuid);
    LIST_FOREACH(team, &db->teams, entries)
    {
        uuid_copy(params.uuid_team, team->uuid);
        LIST_FOREACH(channel, &team->channels, entries)
        {
            uuid_copy(params.uuid_channel, channel->uuid);
            for (int n = 0; n < nbr_threads_per_channel; n++) {
                sprintf(title, "H%d", n);
                sprintf(msg, "%s message", title);
                cr_assert_eq(create_thread(db, title, msg, &params), SUCCESS);
            }
        }
    }
}

static void travel_threads_to_add_replies(
    database_t *db, uuid_selector_t *params, channel_t *channel)
{
    thread_t *thread;
    char msg[SIZE_BODY];

    bzero(msg, SIZE_BODY);
    uuid_copy(params->uuid_channel, channel->uuid);
    LIST_FOREACH(thread, &channel->threads, entries)
    {
        uuid_copy(params->uuid_thread, thread->uuid);
        for (int n = 1; n <= nbr_replies_per_thread; n++) {
            sprintf(msg, "%s R%d", thread->title, n);
            cr_assert_eq(
                create_reply(db, LIST_FIRST(&db->users), msg, params), SUCCESS);
        }
    }
}

static void create_replies(database_t *db)
{
    team_t *team;
    channel_t *channel;
    uuid_selector_t params;

    bzero(&params, sizeof(uuid_selector_t));
    uuid_copy(params.uuid_user, LIST_FIRST(&db->users)->uuid);
    LIST_FOREACH(team, &db->teams, entries)
    {
        uuid_copy(params.uuid_team, team->uuid);
        LIST_FOREACH(channel, &team->channels, entries)
        {
            travel_threads_to_add_replies(db, &params, channel);
        }
    }
}

static void check_users_size(const database_t *db, const int expected_users)
{
    user_t *user;
    int users_size = 0;

    LIST_FOREACH(user, &db->users, entries)
    users_size++;
    cr_assert_eq(users_size, expected_users);
}

static void check_private_messages_size(
    const database_t *db, const int expected_msg_per_user)
{
    user_t *user;
    private_msg_t *private_msg;
    int pm_size = 0;

    LIST_FOREACH(user, &db->users, entries)
    {
        pm_size = 0;
        LIST_FOREACH(private_msg, &user->messages, entries)
        pm_size++;
        cr_assert_eq(pm_size, expected_msg_per_user);
    }
}

static void check_teams_size(const database_t *db, const int expected_teams)
{
    team_t *team;
    int teams_size = 0;

    LIST_FOREACH(team, &db->teams, entries)
    teams_size++;
    cr_assert_eq(teams_size, expected_teams);
}

static void check_channels_size(
    const database_t *db, const int expected_channels_per_team)
{
    team_t *team;
    channel_t *channel;
    int channels_size = 0;

    LIST_FOREACH(team, &db->teams, entries)
    {
        channels_size = 0;
        LIST_FOREACH(channel, &team->channels, entries)
        channels_size++;
        cr_assert_eq(channels_size, expected_channels_per_team);
    }
}

static void check_threads_size(const database_t *db)
{
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    int threads_size = 0;

    LIST_FOREACH(team, &db->teams, entries)
    LIST_FOREACH(channel, &team->channels, entries)
    {
        threads_size = 0;
        LIST_FOREACH(thread, &channel->threads, entries)
        threads_size++;
        cr_assert_eq(threads_size, nbr_threads_per_channel);
    }
}

static void check_replies_size(const database_t *db)
{
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    reply_t *reply;
    int replies_size = 0;

    LIST_FOREACH(team, &db->teams, entries)
    LIST_FOREACH(channel, &team->channels, entries)
    LIST_FOREACH(thread, &channel->threads, entries)
    {
        replies_size = 0;
        LIST_FOREACH(reply, &thread->replies, entries)
        replies_size++;
        cr_assert_eq(replies_size, nbr_replies_per_thread);
    }
}

static void check_saved_private_messages(
    const user_t *user, const int nbr_pm_per_user)
{
    private_msg_t *private_msg;
    uuid_selector_t selector;
    char message[SIZE_BODY];
    int n = 1;

    bzero(message, SIZE_BODY);
    bzero(&selector, sizeof(uuid_selector_t));
    LIST_FOREACH(private_msg, &user->messages, entries)
    {
        sprintf(message, "%s M%d", user->username, n++);
        cr_assert_str_eq(private_msg->body, message);
    }
    cr_assert_eq(n - 1, nbr_pm_per_user);
}

static void check_saved_users(const int nbr_users, const int nbr_private_msgs)
{
    database_t db;
    user_t *user;
    char username[SIZE_NAME];
    int users_size = 0;

    bzero(username, SIZE_NAME);
    cr_assert_eq(load_database(&db), true);

    LIST_FOREACH(user, &db.users, entries)
    {
        users_size++;
        sprintf(username, "U%d", users_size);
        cr_assert_str_eq(user->username, username);
        check_saved_private_messages(user, nbr_private_msgs);
    }
    cr_assert_eq(users_size, nbr_users);
    destroy_database_t(&db);
}

static void check_saved_replies(const thread_t *thread)
{
    reply_t *reply;
    char msg[SIZE_BODY];
    int replies_size = 1;

    bzero(msg, SIZE_BODY);
    LIST_FOREACH(reply, &thread->replies, entries)
    {
        sprintf(msg, "%s R%d", thread->title, replies_size++);
        cr_assert_str_eq(reply->body, msg);
    }
    cr_assert_eq(replies_size - 1, nbr_replies_per_thread);
}

static void check_saved_threads(const channel_t *channel)
{
    thread_t *thread;
    char title[SIZE_NAME];
    char message[SIZE_BODY];
    int threads_size = 0;

    bzero(title, SIZE_NAME);
    bzero(message, SIZE_BODY);
    LIST_FOREACH(thread, &channel->threads, entries)
    {
        sprintf(title, "H%d", threads_size++);
        sprintf(message, "%s message", title);
        cr_assert_str_eq(thread->title, title);
        cr_assert_str_eq(thread->body, message);
        check_saved_replies(thread);
    }
    cr_assert_eq(threads_size, nbr_threads_per_channel);
}

static void check_saved_channels(
    const team_t *team, const int nbr_channels_per_team)
{
    channel_t *channel;
    char name[SIZE_NAME];
    char description[SIZE_DESC];
    int n = 1;

    bzero(name, SIZE_NAME);
    bzero(description, SIZE_DESC);
    LIST_FOREACH(channel, &team->channels, entries)
    {
        sprintf(name, "C%d", n++);
        sprintf(description, "%s description", name);
        cr_assert_str_eq(channel->name, name);
        cr_assert_str_eq(channel->description, description);
        check_saved_threads(channel);
    }
    cr_assert_eq(n - 1, nbr_channels_per_team);
}

static void check_saved_teams(const int nbr_teams, const int nbr_channels)
{
    database_t db;
    team_t *team;
    char teamname[SIZE_NAME];
    char teamdesc[SIZE_DESC];
    int teams_size = 0;

    bzero(teamname, SIZE_NAME);
    bzero(teamdesc, SIZE_DESC);
    cr_assert_eq(load_database(&db), true);
    LIST_FOREACH(team, &db.teams, entries)
    {
        sprintf(teamname, "T%d", ++teams_size);
        sprintf(teamdesc, "%s description", teamname);
        cr_assert_str_eq(team->name, teamname);
        cr_assert_str_eq(team->description, teamdesc);
        check_saved_channels(team, nbr_channels);
    }
    cr_assert_eq(teams_size, nbr_teams);
    destroy_database_t(&db);
}

// Test save db with users & load it
Test(save_load_db, t01)
{
    const int nbr_users = 5;
    database_t db;

    create_empty_database(&db);
    create_users(&db, nbr_users);
    check_users_size(&db, nbr_users);
    cr_assert_eq(save_database(&db), true);
    destroy_database_t(&db);
    check_saved_users(nbr_users, 0);
    remove(DB_FILEPATH);
}

// Test save db with users & load it
Test(save_load_db, t02)
{
    const int nbr_users = 5;
    const int nbr_private_msgs = 8;
    database_t db;

    create_empty_database(&db);
    create_users(&db, nbr_users);
    create_private_messages(&db, nbr_private_msgs);
    check_users_size(&db, nbr_users);
    check_private_messages_size(&db, nbr_private_msgs);
    cr_assert_eq(save_database(&db), true);
    destroy_database_t(&db);
    check_saved_users(nbr_users, nbr_private_msgs);
    remove(DB_FILEPATH);
}

// Test save db with users & teams & load them
Test(save_load_db, t03)
{
    const int nbr_users = 5;
    const int nbr_teams = 6;
    database_t db;

    create_empty_database(&db);
    create_users(&db, nbr_users);
    create_teams(&db, nbr_teams);
    check_users_size(&db, nbr_users);
    check_teams_size(&db, nbr_teams);
    cr_assert_eq(save_database(&db), true);
    destroy_database_t(&db);
    check_saved_users(nbr_users, 0);
    check_saved_teams(nbr_teams, 0);
    remove(DB_FILEPATH);
}

// Test save db with users & teams & channels & threads & load them
Test(save_load_db, t04)
{
    const int nbr_users = 5;
    const int nbr_teams = 4;
    const int nbr_channels = 2;
    database_t db;

    create_empty_database(&db);
    create_users(&db, nbr_users);
    create_teams(&db, nbr_teams);
    create_channels(&db, nbr_channels);
    create_threads(&db);
    create_replies(&db);
    check_users_size(&db, nbr_users);
    check_teams_size(&db, nbr_teams);
    check_channels_size(&db, nbr_channels);
    check_threads_size(&db);
    check_replies_size(&db);
    cr_assert_eq(save_database(&db), true);
    destroy_database_t(&db);
    check_saved_users(nbr_users, 0);
    check_saved_teams(nbr_teams, nbr_channels);
    remove(DB_FILEPATH);
}

// Test save db with users & pv msg & teams & channels & threads & load them
const int nbr_users = 5;
const int nbr_teams = 4;
const int nbr_channels = 3;
const int nbr_private_messages = 7;
Test(save_load_db, t05)
{
    database_t db;

    create_empty_database(&db);
    create_users(&db, nbr_users);
    create_private_messages(&db, nbr_private_messages);
    create_teams(&db, nbr_teams);
    create_channels(&db, nbr_channels);
    create_threads(&db);
    create_replies(&db);
    check_users_size(&db, nbr_users);
    check_teams_size(&db, nbr_teams);
    check_channels_size(&db, nbr_channels);
    check_threads_size(&db);
    check_replies_size(&db);
    check_private_messages_size(&db, nbr_private_messages);
    cr_assert_eq(save_database(&db), true);
    destroy_database_t(&db);
    check_saved_users(nbr_users, nbr_private_messages);
    check_saved_teams(nbr_teams, nbr_channels);
    remove(DB_FILEPATH);
}
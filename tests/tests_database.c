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

// Test save empty db
Test(save_db, t01)
{
    database_t *db = create_empty_database();

    cr_assert_neq(db, NULL);
    cr_assert_eq(save_database(db), true);
    free(db);
}

static void create_users(database_t *db, const int nbr_users)
{
    char username[8];

    for (int i = 1; i <= nbr_users; i++) {
        sprintf(username, "USER%d", i);
        cr_assert_eq(create_user(db, username, NULL), SUCCESS);
    }
}

static void create_teams(database_t *db, const int nbr_teams)
{
    char name[16];
    char description[32];

    for (int i = 1; i <= nbr_teams; i++) {
        sprintf(name, "TEAM%d", i);
        sprintf(description, "%s description", name);
        cr_assert_eq(create_team(db, name, description, NULL), SUCCESS);
    }
}

static void create_channels(database_t *db, const int nbr_channel_per_team)
{
    team_t *team;
    uuid_selector_t selector;
    char name[16];
    char description[32];
    int i = 1;

    bzero(&selector, sizeof(uuid_selector_t));
    LIST_FOREACH(team, &db->teams, entries)
    {
        uuid_copy(selector.uuid_team, team->uuid);
        for (int n = 0; n < nbr_channel_per_team; n++) {
            sprintf(name, "CHANNEL%d", i++);
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
    char title[32];
    char msg[64];

    bzero(&params, sizeof(uuid_selector_t));
    uuid_copy(params.uuid_user, LIST_FIRST(&db->users)->uuid);
    LIST_FOREACH(team, &db->teams, entries) {
        uuid_copy(params.uuid_team, team->uuid);
        LIST_FOREACH(channel, &team->channels, entries) {
            uuid_copy(params.uuid_channel, channel->uuid);
            for (int n = 0; n < nbr_threads_per_channel; n++) {
                sprintf(
                    title, "%s %s THREAD%d", team->name, channel->name, n);
                sprintf(msg, "%s message", title);
                cr_assert_eq(create_thread(db, title, msg, &params), SUCCESS);
            }
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

static void check_saved_users(const int nbr_users)
{
    database_t *db = load_database();
    user_t *user;
    char username[8];
    int users_size = 0;

    cr_assert_neq(db, NULL);

    LIST_FOREACH(user, &db->users, entries)
    {
        users_size++;
        sprintf(username, "USER%d", users_size);
        cr_assert_str_eq(user->username, username);
    }
    cr_assert_eq(users_size, nbr_users);
    destroy_database_t(db);
}

static void check_saved_threads(const team_t *team, const channel_t *channel)
{
    thread_t *thread;
    uuid_selector_t selector;
    char title[32];
    char message[64];
    int threads_size = 0;

    bzero(&selector, sizeof(uuid_selector_t));
    LIST_FOREACH(thread, &channel->threads, entries)
    {
        sprintf(title, "%s %s THREAD%d", team->name, channel->name,
            threads_size++);
        sprintf(message, "%s message", title);
        cr_assert_str_eq(thread->title, title);
        cr_assert_str_eq(thread->body, message);
    }
    cr_assert_eq(threads_size, nbr_threads_per_channel);
}

static void check_saved_channels(
    const team_t *team, int *channels_size, const int nbr_channels_per_team)
{
    channel_t *channel;
    uuid_selector_t selector;
    char name[16];
    char description[32];
    int n = 0;

    if (nbr_channels_per_team <= 0)
        return;
    bzero(&selector, sizeof(uuid_selector_t));
    LIST_FOREACH(channel, &team->channels, entries)
    {
        sprintf(name, "CHANNEL%d", (*channels_size)--);
        sprintf(description, "%s description", name);
        cr_assert_str_eq(channel->name, name);
        cr_assert_str_eq(channel->description, description);
        n++;
        check_saved_threads(team, channel);
    }
    cr_assert_eq(n, nbr_channels_per_team);
}

static void check_saved_teams(const int nbr_teams, const int nbr_channels)
{
    database_t *db = load_database();
    team_t *team;
    char teamname[8];
    char teamdesc[32];
    int teams_size = 0;
    int channels_size = nbr_channels * nbr_teams;

    cr_assert_neq(db, NULL);
    LIST_FOREACH(team, &db->teams, entries)
    {
        sprintf(teamname, "TEAM%d", ++teams_size);
        sprintf(teamdesc, "%s description", teamname);
        cr_assert_str_eq(team->name, teamname);
        cr_assert_str_eq(team->description, teamdesc);
        check_saved_channels(team, &channels_size, nbr_channels);
    }
    cr_assert_eq(teams_size, nbr_teams);
    cr_assert_eq(channels_size, 0);
    destroy_database_t(db);
}

// Test save db with users & load it
Test(save_load_db, t01)
{
    const int nbr_users = 5;
    database_t *db = create_empty_database();

    cr_assert_neq(db, NULL);
    create_users(db, nbr_users);
    check_users_size(db, nbr_users);
    cr_assert_eq(save_database(db), true);
    destroy_database_t(db);
    check_saved_users(nbr_users);
}

// Test save db with users & teams & load them
Test(save_load_db, t02)
{
    const int nbr_users = 5;
    const int nbr_teams = 10;
    database_t *db = create_empty_database();

    cr_assert_neq(db, NULL);
    create_users(db, nbr_users);
    create_teams(db, nbr_teams);
    check_users_size(db, nbr_users);
    check_teams_size(db, nbr_teams);
    cr_assert_eq(save_database(db), true);
    destroy_database_t(db);
    check_saved_users(nbr_users);
    check_saved_teams(nbr_teams, 0);
}

// Test save db with users & teams & channels & threads & load them
Test(save_load_db, t03)
{
    const int nbr_users = 5;
    const int nbr_teams = 10;
    const int nbr_channels = 1;
    database_t *db = create_empty_database();

    cr_assert_neq(db, NULL);
    create_users(db, nbr_users);
    create_teams(db, nbr_teams);
    create_channels(db, nbr_channels);
    create_threads(db);
    check_users_size(db, nbr_users);
    check_teams_size(db, nbr_teams);
    check_channels_size(db, nbr_channels);
    check_threads_size(db);

    cr_assert_eq(save_database(db), true);
    destroy_database_t(db);
    check_saved_users(nbr_users);
    check_saved_teams(nbr_teams, nbr_channels);
}
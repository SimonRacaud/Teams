/*
** EPITECH PROJECT, 2021
** tests
** File description:
** tests_database.c - Created: 20/05/2021
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "database.h"

// Test save empty db
Test(save_db, t01)
{
    database_t *db = create_empty_database();

    cr_assert_neq(db, NULL);
    if (db == NULL)
        return;
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
    char teamname[8];
    char teamdesc[32];

    for (int i = 1; i <= nbr_teams; i++) {
        sprintf(teamname, "TEAM%d", i);
        sprintf(teamdesc, "%s description", teamname);
        cr_assert_eq(create_team(db, teamname, teamdesc, NULL), SUCCESS);
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

static void check_saved_users(const int nbr_users)
{
    database_t *db = load_database();
    user_t *user;
    char username[8];
    int users_size = 0;

    cr_assert_neq(db, NULL);
    if (db == NULL)
        return;

    LIST_FOREACH(user, &db->users, entries)
    {
        users_size++;
        sprintf(username, "USER%d", users_size);
        cr_assert_str_eq(user->username, username);
    }
    cr_assert_eq(users_size, nbr_users);
    destroy_database_t(db);
}

static void check_saved_teams(const int nbr_teams)
{
    database_t *db = load_database();
    team_t *team;
    char teamname[8];
    char teamdesc[32];
    int teams_size = 0;

    cr_assert_neq(db, NULL);
    if (db == NULL)
        return;

    LIST_FOREACH(team, &db->teams, entries)
    {
        teams_size++;
        sprintf(teamname, "TEAM%d", teams_size);
        sprintf(teamdesc, "%s description", teamname);
        cr_assert_str_eq(team->name, teamname);
        cr_assert_str_eq(team->description, teamdesc);
    }
    cr_assert_eq(teams_size, nbr_teams);
    destroy_database_t(db);
}

// Test save db with users & load it
Test(save_load_db, t01)
{
    const int nbr_users = 5;
    database_t *db = create_empty_database();

    cr_assert_neq(db, NULL);
    if (db == NULL)
        return;
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
    if (db == NULL)
        return;
    create_users(db, nbr_users);
    create_teams(db, nbr_teams);
    check_users_size(db, nbr_users);
    check_teams_size(db, nbr_teams);
    cr_assert_eq(save_database(db), true);
    destroy_database_t(db);
    check_saved_users(nbr_users);
    check_saved_teams(nbr_teams);
}
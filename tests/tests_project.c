/*
** EPITECH PROJECT, 2021
** Unit_Test_Criterion
** File description:
** Test File
*/

#include <unistd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "network.h"
#include "database.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// Test(function, t01, .init = redirect_all_stdout)
//{
//    cr_assert_stderr_eq_str("");
//}

Test(cli_request_parser, t01)
{
    request_t *req = request_create("/hello \"world\"");

    if (req == NULL) {
        fprintf(stderr, "NULL REQUEST\n");
    }
    cr_expect_str_eq(req->label, "hello");
    cr_expect_str_eq(req->args[0], "world");
    cr_assert_eq(req->args[1], NULL);
}

Test(cli_request_parser, t02)
{
    request_t *req = request_create("/hello");

    if (req == NULL) {
        fprintf(stderr, "NULL REQUEST\n");
    }
    cr_expect_str_eq(req->label, "hello");
    cr_assert_eq(req->args, NULL);
}

Test(cli_request_parser, t03)
{
    request_t *req = request_create("/hello \"world\" \" world \"");

    if (req == NULL) {
        fprintf(stderr, "NULL REQUEST\n");
    }
    cr_expect_str_eq(req->label, "hello");
    cr_expect_str_eq(req->args[0], "world");
    cr_expect_str_eq(req->args[1], " world ");
    cr_assert_eq(req->args[2], NULL);
}

Test(cli_request_parser, t04)
{
    request_t *req = request_create("/ hello ");

    cr_assert_eq(req, NULL);
}

Test(cli_request_parser, t05)
{
    request_t *req = request_create("/hello \"world\" \r");

    cr_assert_eq(req, NULL);
}

Test(cli_request_parser, t06)
{
    request_t *req = request_create("/hello world");

    cr_assert_eq(req, NULL);
}

Test(cli_request_parser, t07)
{
    request_t *req = request_create("/hello \"world ");

    cr_assert_eq(req, NULL);
}

Test(cli_request_parser, t08)
{
    request_t *req = request_create("/hello world\" ");

    cr_assert_eq(req, NULL);
}

Test(cli_request_parser, t09)
{
    request_t *req = request_create("/hello \t \"world\" \t \t ");

    cr_assert_neq(req, NULL);
}

Test(cli_request_parser, t10)
{
    request_t *req = request_create("/ ");

    cr_assert_str_eq(req->label, "");
    cr_assert_eq(req->args, NULL);
}

Test(cli_request_parser, t11)
{
    request_t *req = request_create("");

    cr_assert_eq(req, NULL);
}

Test(cli_request_parser, t12)
{
    request_t *req = request_create("");

    cr_assert_eq(req, NULL);
}

Test(request_write, t01)
{
    int fds[2];
    int res = pipe(fds);
    socket_t sock = {.fd = fds[1]};
    request_t req = {.receiver = &sock, .label = "Hello", .args = NULL};
    char buffer[100];
    int len;

    cr_assert_eq(request_write(&req), EXIT_SUCCESS);
    len = read(fds[0], buffer, 99);
    buffer[len] = '\0';
    cr_assert_str_eq(buffer, "Hello");
    cr_assert_eq(buffer[6], '\r');
    cr_assert_eq(buffer[7], '\n');
}

Test(request_parse, t01)
{
    request_t *req = request_parse("Hello\0World\0\r\n");

    cr_assert_str_eq(req->label, "Hello");
    cr_assert_str_eq(req->args[0], "World");
    cr_assert_eq(req->args[1], NULL);
}

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

// Test save db with users & load it
static void check_saved_users(const int nbr_users)
{
    database_t *db = load_database();
    user_t *user;
    char username[8];
    size_t users_size = 0;

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

Test(save_load_db, t01)
{
    const int nbr_users = 5;
    database_t *db = create_empty_database();
    size_t users_size = 0;
    user_t *user;
    char username[8];

    cr_assert_neq(db, NULL);
    if (db == NULL)
        return;
    for (int i = 1; i <= nbr_users; i++) {
        sprintf(username, "USER%d", i);
        cr_assert_eq(create_user(db, username, NULL), SUCCESS);
    }
    LIST_FOREACH(user, &db->users, entries)
    users_size++;
    cr_assert_eq(users_size, nbr_users);
    cr_assert_eq(save_database(db), true);
    destroy_database_t(db);
    check_saved_users(nbr_users);
}
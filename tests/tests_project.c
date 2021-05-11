/*
** EPITECH PROJECT, 2021
** Unit_Test_Criterion
** File description:
** Test File
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "parser.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// Test(function, t01, .init = redirect_all_stdout)
//{
//
//     cr_assert_stderr_eq_str("");
// }

Test(request_parser, t01)
{
    request_t *req = request_create("/hello \"world\"\r\n");

    if (req == NULL) {
        fprintf(stderr, "NULL REQUEST\n");
    }
    cr_expect_str_eq(req->label, "hello");
    cr_expect_str_eq(req->args[0], "world");
    cr_assert_eq(req->args[1], NULL);
}

Test(request_parser, t02)
{
    request_t *req = request_create("/hello\r\n");

    if (req == NULL) {
        fprintf(stderr, "NULL REQUEST\n");
    }
    cr_expect_str_eq(req->label, "hello");
    cr_assert_eq(req->args, NULL);
}

Test(request_parser, t03)
{
    request_t *req = request_create("/hello \"world\" \" world \"\r\n");

    if (req == NULL) {
        fprintf(stderr, "NULL REQUEST\n");
    }
    cr_expect_str_eq(req->label, "hello");
    cr_expect_str_eq(req->args[0], "world");
    cr_expect_str_eq(req->args[1], " world ");
    cr_assert_eq(req->args[2], NULL);
}

Test(request_parser, t04)
{
    request_t *req = request_create("/ hello \r\n");

    cr_assert_eq(req, NULL);
}

Test(request_parser, t05)
{
    request_t *req = request_create("/hello \"world\" ");

    cr_assert_eq(req, NULL);
}

Test(request_parser, t06)
{
    request_t *req = request_create("/hello world\r\n");

    cr_assert_eq(req, NULL);
}

Test(request_parser, t07)
{
    request_t *req = request_create("/hello \"world \r\n");

    cr_assert_eq(req, NULL);
}

Test(request_parser, t08)
{
    request_t *req = request_create("/hello world\" \r\n");

    cr_assert_eq(req, NULL);
}

Test(request_parser, t09)
{
    request_t *req = request_create("/hello \t \"world\" \t \t \r\n");

    cr_assert_neq(req, NULL);
}

Test(request_parser, t10)
{
    request_t *req = request_create("/ \r\n");

    cr_assert_str_eq(req->label, "");
    cr_assert_eq(req->args, NULL);
}

Test(request_parser, t11)
{
    request_t *req = request_create("\r\n");

    cr_assert_eq(req, NULL);
}

Test(request_parser, t12)
{
    request_t *req = request_create("");

    cr_assert_eq(req, NULL);
}
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

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

//Test(function, t01, .init = redirect_all_stdout)
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
    cr_assert_str_eq(buffer, "Hello\r\r\r\n");
}

Test(request_parse, t01)
{
    request_t *req = request_parse("Hello\r\rWorld\r\r");

    cr_assert_str_eq(req->label, "Hello");
    cr_assert_str_eq(req->args[0], "World");
    cr_assert_eq(req->args[1], NULL);
}

Test(response, t01)
{
    int fds[2];
    int x = pipe(fds);
    socket_t soc = {.fd = fds[1]};
    request_t *req = request_create("/help \"bob\"  \"KOK\"  ");
    response_t *res = response_create(ERROR, req, &soc, NULL);
    buffer_t buffer = {0};

    cr_assert_neq(res, NULL);
    cr_assert_str_eq(res->req_label, "help");
    cr_assert_str_eq(res->req_args[0], "bob");
    cr_assert_eq(res->err_code, ERROR);
    cr_assert_eq(response_send(res), EXIT_SUCCESS);
    res = response_read(fds[0], &buffer);
    cr_assert_neq(res, NULL);
    cr_assert_eq(res->err_code, ERROR);
    cr_assert_str_eq(res->req_label, "help");
    cr_assert_str_eq(res->req_args[0], "bob");
    cr_assert_str_eq(res->req_args[1], "KOK");
}
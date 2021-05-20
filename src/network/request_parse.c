/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 11/05/2021 request_read.c
*/

#include "network/request_t.h"
#include "utility.h"
#include "socket.h"
#include "env.h"

static const format_t FIELD_FORMAT = {
    .prefix = NULL,
    .suffix_chars = NULL,
    .accept_null_suffix = false,
    .suffix = "\r\r",
    .exclude = NULL,
    .is_alpha = false,
    .is_num = false,
    .no_body = false
};

static int parse_args(request_t *req, char *ptr)
{
    req->args = walloc(NULL, 0);
    if (!req->args)
        return EXIT_FAILURE;
    for (size_t idx = 0; true; idx++) {
        if (ptr[0] == '\0') {
            return EXIT_SUCCESS;
        }
        req->args[idx] = strdup_format(ptr, &FIELD_FORMAT, &ptr);
        if (!req->args[idx])
            return EXIT_FAILURE;
        ptr += 2;
        req->args = walloc(req->args, idx + 1);
        if (!req->args)
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static int parser(request_t *req, char *input)
{
    char *ptr = input;

    req->label = strdup_format(ptr, &FIELD_FORMAT, &ptr);
    if (!req->label)
        return EXIT_FAILURE;
    ptr += 2;
    if (parse_args(req, ptr) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

request_t *request_parse(char *input)
{
    request_t *req = malloc(sizeof(request_t));

    if (!req)
        return NULL;
    if (parser(req, input) == EXIT_FAILURE)
        return NULL;
    return req;
}
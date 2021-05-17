/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 request_parse.c
*/

#include "utility.h"
#include "network/request_t.h"
#include "format_t.h"

static const format_t INPUT_LABEL_FORMAT = {
    .prefix = "/",
    .suffix_chars = " \t",
    .suffix = NULL,
    .accept_null_suffix = true,
    .exclude = NULL,
    .is_alpha = true,
    .is_num = true,
    .no_body = false
};

static const format_t INPUT_END_FORMAT = {
    .prefix = NULL,
    .suffix_chars = "",
    .suffix = NULL,
    .accept_null_suffix = true,
    .exclude = NULL,
    .is_alpha = false,
    .is_num = false,
    .no_body = true
};

static const format_t INPUT_ARG_FORMAT = {
    .prefix = "\"",
    .suffix_chars = "\"",
    .suffix = NULL,
    .accept_null_suffix = false,
    .exclude = NULL,
    .is_alpha = false,
    .is_num = false,
    .no_body = false
};

static char *skip_spaces(char *str)
{
    size_t i = 0;

    while (str[i] != '\0') {
        if (str[i] != ' ' && str[i] != '\t') {
            return str + i;
        }
        i++;
    }
    return str + i;
}

static int parse_input_args(request_t *req, char *ptr)
{
    req->args = walloc(NULL, 0);
    if (!req->args)
        return EXIT_FAILURE;
    for (size_t idx = 0; true; idx++) {
        if (cmp_format(ptr, &INPUT_END_FORMAT))
            return EXIT_SUCCESS;
        req->args[idx] = strdup_format(ptr, &INPUT_ARG_FORMAT, &ptr);
        if (!req->args[idx])
            return EXIT_FAILURE;
        ptr = skip_spaces(ptr);
        req->args = walloc(req->args, idx + 2);
    }
    return EXIT_SUCCESS;
}

static int parse_input(request_t *req, char *command)
{
    char *ptr = NULL;

    req->label = strdup_format(command, &INPUT_LABEL_FORMAT, &ptr);
    if (req->label == NULL)
        return EXIT_FAILURE;
    if ((size_t)(ptr - command) > strlen(command))
        ptr = &command[strlen(command)];
    ptr = skip_spaces(ptr);
    return parse_input_args(req, ptr);
}

request_t *request_create(char *command)
{
    request_t *req = malloc(sizeof(request_t));

    if (!req)
        return NULL;
    req->receiver = NULL;
    req->args = NULL;
    if (parse_input(req, command) == EXIT_FAILURE) {
        free(req);
        return NULL;
    }
    if (!req->args[0]) {
        free(req->args);
        req->args = NULL;
    }
    return req;
}
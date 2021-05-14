/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 11/05/2021 response_create.c
*/

#include "utility.h"
#include "network/request_t.h"
#include "network/response_t.h"

static int copy_args(request_t *request, response_t *res)
{
    size_t len = 0;

    while (request->args[len] != NULL)
        len++;
    res->req_args = malloc(sizeof(char *) * (len + 1));
    if (!res->req_args)
        return EXIT_FAILURE;
    res->req_args[len] = NULL;
    for (size_t i = 0; request->args[i] != NULL; i++) {
        res->req_args[i] = strdup(request->args[i]);
        if (!res->req_args[i])
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

response_t *response_create(
    rcode_e code, request_t *request, socket_t *client, void *body)
{
    response_t *res = malloc(sizeof(response_t));

    if (!res)
        return NULL;
    res->receiver = client;
    res->err_code = code;
    res->req_label = strdup(request->label);
    res->req_args = NULL;
    if (request->args) {
        if (copy_args(request, res) == EXIT_FAILURE) {
            free(res->req_label);
            return NULL;
        }
    }
    res->header = NULL;
    res->body = body;
    return res;
}
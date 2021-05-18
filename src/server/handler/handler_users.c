/*
** EPITECH PROJECT, 2021
** handler_users.c
** File description:
** handler_users function
*/

#include <math.h>
#include "server.h"
#include "request_handler_t.h"

static inline size_t get_nb_length(int nb)
{
    return floor(log10(abs(nb))) + 1;
}

static bool dup_list(database_t *db, char *user_list)
{
    int size = 0;
    size_t it = 0;
    size_t pos = 0;
    user_t *user = NULL;

    LIST_FOREACH(user, &db->users, entries) {
        size = sprintf(user_list + pos, "%li. %s\n", it++, user->username);
        if (size < 0)
            return false;
        pos += size;
    }
    user_list[pos - 1] = '\0';
    return true;
}

static char *get_users_list(database_t *db)
{
    size_t it = 0;
    int size = 0;
    char *user_list = NULL;
    user_t *user = NULL;

    LIST_FOREACH(user, &db->users, entries)
        size += (strlen(user->username) + get_nb_length(it++) + 4);
    if (!size)
        return strdup("No users found!");
    user_list = malloc(sizeof(char) * size);
    if (!user_list)
        return NULL;
    if (!dup_list(db, user_list))
        return NULL;
    return user_list;
}

static void *get_body(database_t *db)
{
    body_header_t body_struct = {0};
    const char type[] = "string";
    char *list = get_users_list(db);
    void *body = NULL;

    if (!list)
        return NULL;
    body = malloc(sizeof(body_header_t) + strlen(list) + 1);
    if (!body)
        return NULL;
    body_struct.list_size = 1;
    body_struct.elem_size = strlen(list) + 1;
    memcpy(body_struct.type, type, strlen(type));
    memcpy(body, &body_struct, sizeof(body_header_t));
    memcpy(body + sizeof(body_header_t), list, body_struct.elem_size);
    free(list);
    return body;
}

int handler_users(server_t *srv, request_t *request)
{
    response_t *response = NULL;
    int return_value = 0;
    void *body = NULL;

    if (!srv || !request)
        return EXIT_FAILURE;
    body = get_body(&srv->database);
    if (!body)
        return EXIT_FAILURE;
    response = response_create(SUCCESS, request, request->receiver, body);
    if (!response)
        return EXIT_FAILURE;
    return_value = response_send(response);
    response_destroy(response);
    return return_value;
}
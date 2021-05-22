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

int handler_users(server_t *srv, request_t *request, UNUSED client_t *client)
{
    int return_value = 0;
    char *list = NULL;

    if (!srv || !request)
        return EXIT_FAILURE;
    list = get_users_list(&srv->database);
    if (!list)
        return EXIT_FAILURE;
    return_value = reply_str(srv, SUCCESS, request, list);
    free(list);
    return return_value;
}
/*
** EPITECH PROJECT, 2021
** main.c
** File description:
** main function
*/

#include "server.h"
#include "utility.h"
#include "database.h"

static int usage(const char *bin, int status)
{
    printf("USAGE: %s port\n\n", bin);
    printf(
        "\t\tport\tis the port number on which the server socket listens.\n");
    return status;
}

static int arg_parser(char **argv, int argc, uint *port_ptr)
{
    for (size_t i = 0; argv[i] != NULL; i++) {
        if (!strcmp(argv[i], "-help")) {
            usage(argv[0], EXIT_SUCCESS);
            exit(EXIT_SUCCESS);
        }
    }
    if (argc != 2 || is_number(argv[1]) == false) {
        return usage(argv[0], EXIT_FAILURE);
    }
    *port_ptr = (uint) atoi(argv[1]);
    return EXIT_SUCCESS;
}

static void check_saved_users(database_t *db, const int nbr_users)
{
    user_t *user;
    char username[8];
    int users_size = 0;

    destroy_database_t(db);
    db = load_database();
    if (db == NULL)
        return;

    LIST_FOREACH(user, &db->users, entries)
    {
        users_size++;
        sprintf(username, "USER%d", users_size);
        if (strcmp(user->username, username))
            exit(1);
    }
    destroy_database_t(db);
    if (users_size != nbr_users)
        exit(1);
}

int main(int argc, char **argv)
{
    const int nbr_users = 5;
    database_t *db = create_empty_database();
    int users_size = 0;
    user_t *user;
    char username[8];

    if (db == NULL)
        return 1;
    for (int i = 1; i <= nbr_users; i++) {
        sprintf(username, "USER%d", i);
        if (create_user(db, username, NULL) != SUCCESS)
            return 1;
    }
    LIST_FOREACH(user, &db->users, entries)
    {
        users_size++;
    }
    if (users_size != nbr_users)
        return 1;
    if (!save_database(db))
        return 1;
    check_saved_users(db, nbr_users);
    return 0;

    server_t server = {0};
    uint port = 0;

    if (arg_parser(argv, argc, &port) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (app_create(&server, port) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (app_loop(&server) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (app_destroy(&server) == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

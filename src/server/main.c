/*
** EPITECH PROJECT, 2021
** main.c
** File description:
** main function
*/

#include "server.h"
#include "utility.h"

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

int main(int argc, char **argv)
{
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

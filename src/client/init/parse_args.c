/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 parse_args.c
*/

#include "client.h"

static const int REQUIRED_ARGC = 3;
static const char *HELP = "-help";

static int usage(const char *bin, int code)
{
    printf("USAGE:\t%s ip port\n", bin);
    printf("\tip\tis the server ip address on which the server socket");
    printf(" listens\n");
    printf("\tport\tis the port number on which the server socket listens\n");
    return code;
}

int parse_args(args_t *args, int argc, char **argv)
{
    for (size_t i = 0; i < (size_t) argc; i++) {
        if (strcmp(argv[i], HELP) == 0) {
            exit(usage(argv[0], EXIT_SUCCESS));
        }
    }
    if (argc != REQUIRED_ARGC) {
        return usage(argv[0], EXIT_FAILURE);
    }
    if (!is_number(argv[2]) || !is_ip(argv[1])) {
        printf("ERROR: invalid port value\n");
        return EXIT_FAILURE;
    }
    args->port = (uint) atoi(argv[2]);
    args->ip = argv[1];
    return EXIT_SUCCESS;
}
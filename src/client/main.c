/*
** EPITECH PROJECT, 2021
** main.c
** File description:
** main function
*/

#include "client.h"

int main(int argc, char **argv)
{
    client_t client = {0};

    if (app_init(&client, argc, argv) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (app_loop(&client) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (app_destroy(&client) == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

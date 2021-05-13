/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 prompt.c
*/

#include "client.h"

char *prompt(char **buffer_ptr, bool *disconnect)
{
    char *input = NULL;

    return fd_getline(STDIN_FILENO, buffer_ptr, disconnect);
}
/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 prompt.c
*/

#include "client.h"

char *prompt(buffer_t *buffer, bool *disconnect)
{
    return fd_getline_delim(STDIN_FILENO, buffer, "\n", disconnect);
}
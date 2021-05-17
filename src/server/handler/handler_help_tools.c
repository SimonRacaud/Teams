/*
** EPITECH PROJECT, 2021
** handler_help.c
** File description:
** handler_help function
*/

#include <stdlib.h>

uint get_tab_len(const char **tab)
{
    uint i = 0;

    for (; tab[i]; i++);
    return i;
}

char *add_crlf(char *tram, size_t len)
{
    tram = realloc(tram, len + 3);
    if (!tram)
        return NULL;
    tram[len] = '\r';
    tram[len + 1] = '\n';
    tram[len + 2] = '\0';
    return tram;
}
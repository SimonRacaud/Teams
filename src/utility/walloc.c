/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 11/05/2021 walloc.c
*/

#include "utility.h"

char **walloc(char **prev, size_t nb)
{
    char **res = NULL;

    if (!prev) {
        return calloc(2, sizeof(char *));
    } else {
        res = reallocarray(prev, (nb + 1), sizeof(char *));
        if (!res)
            return NULL;
        res[nb] = NULL;
        return res;
    }
}
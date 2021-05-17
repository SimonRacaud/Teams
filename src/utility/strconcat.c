/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myftp-simon.racaud
** File description:
** 20/04/2021 strconcat.c
*/

#include "utility.h"

char *strconcat(char *a, const char *b)
{
    if (!a) {
        return strdup(b);
    } else {
        a = realloc(a, strlen(a) + strlen(b) + 1);
        if (!a)
            return NULL;
        strcat(a, b);
        return a;
    }
}
/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myftp-simon.racaud
** File description:
** 20/04/2021 is_empty.c
*/

#include "utility.h"

bool is_empty(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isgraph(str[i]) && !isblank(str[i])) {
            return false;
        }
    }
    return true;
}
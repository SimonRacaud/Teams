/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myftp-simon.racaud
** File description:
** 20/04/2021 find_newline.c
*/

#include <stdlib.h>

ssize_t find_newline(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            return (ssize_t)i;
        }
    }
    return -1;
}
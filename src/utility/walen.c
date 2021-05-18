/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 17/05/2021 walen.c
*/

#include "utility.h"

size_t walen(char **word_array)
{
    size_t i = 0;

    while (word_array && word_array[i] != NULL) {
        i++;
    }
    return i;
}
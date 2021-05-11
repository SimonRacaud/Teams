/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 utility.h
*/

#ifndef UTILITY_H
#define UTILITY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "format_t.h"
#include <ctype.h>

int signal_manager(int signum, bool *activator_ptr);

char *strdup_format(char *str, const format_t *ft, char **end_ptr);
bool cmp_format(char *str, const format_t *ft);

#endif // UTILITY_H

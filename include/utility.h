/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 07/05/2021 utility.h
*/

#ifndef UTILITY_H
#define UTILITY_H

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "format_t.h"

int signal_manager(int signum, bool *activator_ptr);
bool is_number(const char *str);
bool is_ip(const char *str);

char *strdup_format(char *str, const format_t *ft, char **end_ptr);
bool cmp_format(char *str, const format_t *ft);

char **walloc(char **prev, size_t nb);

bool is_number(const char *str);

char *strconcat(char *a, const char *b);

#endif // UTILITY_H

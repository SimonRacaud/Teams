/*
** EPITECH PROJECT, 2021
** handler_tools.c
** File description:
** handler_tools function
*/

#include <uuid.h>
#include <stdlib.h>
#include <string.h>

size_t get_arg_size(const char **arg)
{
    size_t size = 0;

    for (; arg[size]; size++);
    return size;
}

void get_uuid_from_string(uuid_t dest, const char *str)
{
    memset(dest, 0, 16);
    memcpy(dest, str, 15);
}
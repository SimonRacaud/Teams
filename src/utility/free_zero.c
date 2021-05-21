/*
** EPITECH PROJECT, 2021
** utility
** File description:
** free_zero.c - Created: 21/05/2021
*/

#include "utility.h"

void free_zero(void *ptr, size_t size)
{
    if (ptr == NULL)
        return;
    bzero(ptr, sizeof(size));
    free(ptr);
}
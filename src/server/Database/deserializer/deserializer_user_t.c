/*
** EPITECH PROJECT, 2021
** deserializer_user_t.c
** File description:
** deserializer_user_t function
*/

#include <stdlib.h>
#include <string.h>
#include "data/user_t.h"
#include "data/database_t.h"
#include "save/bin_user_t.h"

user_t *deserializer_user_t(const bin_user_t *src, const database_t *db)
{
    user_t *dest = NULL;

    if (!src || !db)
        return NULL;
    dest = malloc(sizeof(user_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(user_t));
    return dest;
}
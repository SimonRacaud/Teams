/*
** EPITECH PROJECT, 2021
** deserializer_reply_t.c
** File description:
** deserializer_reply_t function
*/

#include <stdlib.h>
#include <string.h>
#include "data/reply_t.h"
#include "data/database_t.h"
#include "save/bin_reply_t.h"

reply_t *deserializer_reply_t(const bin_reply_t *src, const database_t *db)
{
    reply_t *dest = NULL;

    if (!src || !db)
        return NULL;
    dest = malloc(sizeof(reply_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(reply_t));
    return dest;
}
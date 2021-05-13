/*
** EPITECH PROJECT, 2021
** deserializer_thread_t.c
** File description:
** deserializer_thread_t function
*/

#include <stdlib.h>
#include <string.h>
#include "data/thread_t.h"
#include "data/database_t.h"
#include "save/bin_thread_t.h"

thread_t *deserializer_thread_t(const bin_thread_t *src, const database_t *db)
{
    thread_t *dest = NULL;

    if (!src || !db)
        return NULL;
    dest = malloc(sizeof(thread_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(thread_t));
    return dest;
}
/*
** EPITECH PROJECT, 2021
** deserializer_private_msg_t.c
** File description:
** deserializer_private_msg_t function
*/

#include <stdlib.h>
#include <string.h>
#include "data/database_t.h"
#include "data/private_msg_t.h"
#include "save/bin_private_msg_t.h"

private_msg_t *deserializer_private_msg_t(
    const bin_private_msg_t *src, const database_t *db)
{
    private_msg_t *dest = NULL;

    if (!src || !db)
        return NULL;
    dest = malloc(sizeof(private_msg_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(private_msg_t));
    return dest;
}
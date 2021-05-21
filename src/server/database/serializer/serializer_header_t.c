/*
** EPITECH PROJECT, 2021
** serializer_header_t.c
** File description:
** serializer_bin_header_t function
*/

#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "save/bin_header_t.h"

bin_header_t *serializer_header_t(const database_t *db)
{
    bin_header_t *dest = NULL;

    if (!db)
        return NULL;
    dest = malloc(sizeof(bin_header_t));
    if (!dest)
        return NULL;
    memset(dest, 0, sizeof(bin_header_t));
    fill_data_length(db, dest);
    return dest;
}
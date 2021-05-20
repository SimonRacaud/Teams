/*
** EPITECH PROJECT, 2021
** loader
** File description:
** read_threads.c - Created: 17/05/2021
*/

#include "database.h"

bool read_threads(bin_header_t *header, database_save_t *db, size_t *offset)
{
    for (uint i = 0; i < header->nb_thread; i++) {
        db->threads[i] = malloc(sizeof(bin_thread_t));
        if (db->threads[i] == NULL)
            return false;
        memcpy(db->threads[i], (void *) ((size_t) header + *offset),
            sizeof(bin_thread_t));
        *offset += sizeof(bin_thread_t);
    }
    return true;
}
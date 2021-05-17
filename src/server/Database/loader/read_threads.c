/*
** EPITECH PROJECT, 2021
** loader
** File description:
** read_threads.c - Created: 17/05/2021
*/

#include "database.h"

void read_threads(bin_header_t *header, database_save_t *db, size_t *offset)
{
    for (uint i = 0; i < header->nb_thread; i++) {
        memcpy(
            &db->threads[i], (size_t) header + *offset, sizeof(bin_thread_t));
        *offset += sizeof(bin_thread_t);
    }
}
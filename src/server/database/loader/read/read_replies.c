/*
** EPITECH PROJECT, 2021
** loader
** File description:
** read_replies.c - Created: 17/05/2021
*/

#include "database.h"

bool read_replies(bin_header_t *header, database_save_t *db, size_t *offset)
{
    for (uint i = 0; i < header->nb_reply; i++) {
        db->replies[i] = malloc(sizeof(bin_reply_t));
        if (db->replies[i] == NULL)
            return false;
        memcpy(db->replies[i], (void *) ((size_t) header + *offset),
            sizeof(bin_reply_t));
        *offset += sizeof(bin_reply_t);
    }
    return true;
}
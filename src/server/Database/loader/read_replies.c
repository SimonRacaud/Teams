/*
** EPITECH PROJECT, 2021
** loader
** File description:
** read_replies.c - Created: 17/05/2021
*/

#include "database.h"

void read_replies(bin_header_t *header, database_save_t *db, size_t *offset)
{
    for (uint i = 0; i < header->nb_reply; i++) {
        memcpy(&db->replies[i], (size_t) header + *offset, sizeof(bin_reply_t));
        *offset += sizeof(bin_reply_t);
    }
}
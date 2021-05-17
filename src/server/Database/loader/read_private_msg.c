/*
** EPITECH PROJECT, 2021
** loader
** File description:
** read_private_msg.c - Created: 17/05/2021
*/

#include "database.h"

void read_private_msg(bin_header_t *header, database_save_t *db, size_t *offset)
{
    for (uint i = 0; i < header->nb_private_msg; i++) {
        memcpy(&db->messages[i], (size_t) header + *offset,
            sizeof(bin_private_msg_t));
        *offset += sizeof(bin_private_msg_t);
    }
}
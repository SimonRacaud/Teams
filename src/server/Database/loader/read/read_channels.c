/*
** EPITECH PROJECT, 2021
** loader
** File description:
** read_channels.c - Created: 17/05/2021
*/

#include "database.h"

bool read_channels(bin_header_t *header, database_save_t *db, size_t *offset)
{
    for (uint i = 0; i < header->nb_channel; i++) {
        db->channels[i] = malloc(sizeof(bin_channel_t));
        if (db->channels[i] == NULL)
            return false;
        memcpy(db->channels[i], (void *) ((size_t) header + *offset),
            sizeof(bin_channel_t));
        *offset += sizeof(bin_channel_t);
    }
    return true;
}
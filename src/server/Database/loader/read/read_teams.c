/*
** EPITECH PROJECT, 2021
** loader
** File description:
** read_teams.c - Created: 17/05/2021
*/

#include "database.h"

bool read_teams(bin_header_t *header, database_save_t *db, size_t *offset)
{
    for (uint i = 0; i < header->nb_team; i++) {
        db->teams[i] = malloc(sizeof(bin_team_t));
        if (db->teams[i] == NULL)
            return false;
        memcpy(db->teams[i], (void *) ((size_t) header + *offset),
            sizeof(bin_team_t));
        *offset += sizeof(bin_team_t);
    }
    return true;
}
/*
** EPITECH PROJECT, 2021
** loader
** File description:
** read_teams.c - Created: 17/05/2021
*/

#include "database.h"

void read_teams(bin_header_t *header, database_save_t *db, size_t *offset)
{
    for (uint i = 0; i < header->nb_team; i++) {
        memcpy(&db->teams[i], (size_t) header + *offset, sizeof(bin_team_t));
        *offset += sizeof(bin_team_t);
    }
}
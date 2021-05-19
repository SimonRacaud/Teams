/*
** EPITECH PROJECT, 2021
** loader
** File description:
** read_users.c - Created: 17/05/2021
*/

#include "database.h"

bool read_users(bin_header_t *header, database_save_t *db, size_t *offset)
{
    size_t teams_offset = 0;

    for (uint i = 0; i < header->nb_user; i++) {
        memcpy(&db->users[i], (void *) ((size_t) header + *offset),
            sizeof(bin_user_t));
        *offset += sizeof(bin_user_t);

        for (uint k = 0; k < db->users[i]->nb_subscribed_teams; k++) {
            db->user_teams_list[i] =
                malloc(sizeof(uuid_t) * db->users[i]->nb_subscribed_teams);
            if (!db->user_teams_list[i])
                return false;
            memcpy(&db->user_teams_list[i],
                (void *) ((size_t) header + *offset), sizeof(uuid_t));
            *offset += sizeof(uuid_t);
        }
    }
    return true;
}
/*
** EPITECH PROJECT, 2021
** loader
** File description:
** read_users.c - Created: 17/05/2021
*/

#include "database.h"

bool read_users(bin_header_t *header, database_save_t *db, size_t *offset)
{
    for (uint i = 0; i < header->nb_user; i++) {
        db->users[i] = malloc(sizeof(bin_user_t));
        if (db->users[i] == NULL)
            return false;
        memcpy(db->users[i], (void *) ((size_t) header + *offset),
            sizeof(bin_user_t));
        *offset += sizeof(bin_user_t);

        db->user_teams_list[i] =
            malloc(sizeof(uuid_t) * db->users[i]->nb_subscribed_teams);
        if (!db->user_teams_list[i])
            return false;
        for (uint k = 0; k < db->users[i]->nb_subscribed_teams; k++) {
            memcpy(db->user_teams_list[i][k],
                (void *) ((size_t) header + *offset), sizeof(uuid_t));
            *offset += sizeof(uuid_t);
        }
    }
    return true;
}
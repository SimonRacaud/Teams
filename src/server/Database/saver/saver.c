/*
** EPITECH PROJECT, 2021
** save
** File description:
** save.c - Created: 17/05/2021
*/

#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include "database.h"

static bool write_list(int fd, const void **list, uint n, int size)
{
    for (uint i = 0; i < n; i++)
        if (write(fd, *(list + i), size) == -1)
            return false;
    return true;
}

static bool write_users(int fd, const database_save_t *db)
{
    for (uint i = 0; i < db->head->nb_user; i++) {
        if (write(fd, db->users[i], sizeof(bin_user_t)) == -1)
            return false;
        for (uint k = 0; k < db->users[i]->nb_subscribed_teams; k++)
            if (write(fd, db->user_teams_list[i][k], sizeof(uuid_t)) == -1)
                return false;
    }
    return true;
}

static bool write_database(int fd, const database_save_t *db)
{
    if (write(fd, db->head, sizeof(bin_header_t)) == -1)
        return false;
    if (!write_users(fd, db))
        return false;
    if (!write_list(fd, (const void **) db->teams, db->head->nb_team,
            sizeof(bin_team_t))
        || !write_list(fd, (const void **) db->channels, db->head->nb_channel,
            sizeof(bin_channel_t))
        || !write_list(fd, (const void **) db->threads, db->head->nb_thread,
            sizeof(bin_thread_t))
        || !write_list(fd, (const void **) db->replies, db->head->nb_reply,
            sizeof(bin_reply_t))
        || !write_list(fd, (const void **) db->messages,
            db->head->nb_private_msg, sizeof(bin_private_msg_t)))
        return false;
    return true;
}

bool save_database(const database_t *db)
{
    int fd = open(DB_FILEPATH, O_WRONLY | O_CREAT, 0644);
    database_save_t *db_save = NULL;

    if (fd < 0) {
        printf("save_database => open: %s\n", strerror(errno));
        return false;
    }
    db_save = create_database_save_t(db);
    if (db_save == NULL)
        return false;
    if (!write_database(fd, db_save)) {
        printf("write_database: %s\n", strerror(errno));
        return false;
    }
    destroy_database_save_t(db_save);
    if (close(fd) == -1) {
        printf("save_database => close: %s\n", strerror(errno));
        return false;
    }
    return true;
}
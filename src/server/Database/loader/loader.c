/*
** EPITECH PROJECT, 2021
** loader
** File description:
** loader.c - Created: 17/05/2021
*/

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include "database.h"

static void init_database_save(database_save_t *db)
{
    memset(db->users, 0, sizeof(bin_user_t *) * db->head->nb_user);
    memset(db->user_teams_list, 0, sizeof(uuid_t *) * db->head->nb_user);
    memset(db->teams, 0, sizeof(bin_team_t *) * db->head->nb_team);
    memset(db->channels, 0, sizeof(bin_channel_t *) * db->head->nb_channel);
    memset(db->threads, 0, sizeof(bin_thread_t *) * db->head->nb_thread);
    memset(db->replies, 0, sizeof(bin_reply_t *) * db->head->nb_reply);
    memset(db->messages, 0,
        sizeof(bin_private_msg_t *) * db->head->nb_private_msg);
}

static database_save_t *create_empty_database_save(void *buffer)
{
    database_save_t *db = malloc(sizeof(database_save_t));

    memset(db, 0, sizeof(database_save_t));
    db->head = malloc(sizeof(bin_header_t));
    if (!db->head)
        return NULL;
    memcpy(db->head, buffer, sizeof(bin_header_t));
    db->users = malloc(sizeof(bin_user_t *) * db->head->nb_user);
    db->user_teams_list = malloc(sizeof(uuid_t *) * db->head->nb_user);
    db->teams = malloc(sizeof(bin_team_t *) * db->head->nb_team);
    db->channels = malloc(sizeof(bin_channel_t *) * db->head->nb_channel);
    db->threads = malloc(sizeof(bin_thread_t *) * db->head->nb_thread);
    db->replies = malloc(sizeof(bin_reply_t *) * db->head->nb_reply);
    db->messages =
        malloc(sizeof(bin_private_msg_t *) * db->head->nb_private_msg);
    if (!db->users || !db->user_teams_list || !db->teams || !db->channels
        || !db->threads || !db->replies || !db->messages)
        return NULL;
    init_database_save(db);
    return db;
}

static bool fill_database(bin_header_t *header, database_save_t *db)
{
    size_t offset = sizeof(bin_header_t);

    if (!read_users(header, db, &offset))
        return false;
    read_teams(header, db, &offset);
    read_channels(header, db, &offset);
    read_threads(header, db, &offset);
    read_replies(header, db, &offset);
    read_private_msg(header, db, &offset);
    destroy_database_save_t(db);
    return true;
}

static bool read_database_save(int fd)
{
    bin_header_t *buffer;
    struct stat st;
    database_save_t *db;

    if (fstat(fd, &st) == -1 || S_ISDIR(st.st_mode))
        return false;
    buffer = malloc(st.st_size);
    if (buffer == NULL)
        return false;
    if (read(fd, buffer, st.st_size) <= 0)
        return false;
    db = create_empty_database_save(buffer);
    if (db == NULL)
        return false;
    return fill_database(buffer, db);
}

/**
 * @brief Return true on successfully. Return false otherwise.
 *
 * @param db
 * @return boolean
 */
database_t *load_database(void)
{
    int fd = open(DB_FILEPATH, O_RDONLY);

    if (fd < 0) {
        return NULL;
    }
    if (!read_database_save(fd)) {
        printf("read_database_save: %s\n", strerror(errno));
        return false;
    }
    if (close(fd) == -1) {
        printf("load_database => close: %s\n", strerror(errno));
        return NULL;
    }
    return true;
}
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
#include <stdio.h>
#include "database.h"

static bool fill_database(bin_header_t *header, database_save_t *db)
{
    size_t offset = sizeof(bin_header_t);

    if (!read_users(header, db, &offset))
        return false;
    if (!read_teams(header, db, &offset))
        return false;
    if (!read_channels(header, db, &offset))
        return false;
    if (!read_threads(header, db, &offset))
        return false;
    if (!read_replies(header, db, &offset))
        return false;
    if (!read_private_msg(header, db, &offset))
        return false;
    return true;
}

static database_save_t *read_database_save(int fd)
{
    bin_header_t *buffer;
    struct stat st;
    database_save_t *db;

    if (fstat(fd, &st) == -1 || S_ISDIR(st.st_mode))
        return NULL;
    buffer = malloc(st.st_size);
    if (buffer == NULL)
        return NULL;
    if (read(fd, buffer, st.st_size) < st.st_size)
        return NULL;
    db = create_empty_database_save(buffer);
    if (db == NULL)
        return NULL;
    if (!fill_database(buffer, db))
        return NULL;
    free_zero(buffer, st.st_size);
    return db;
}

bool load_database(database_t *db)
{
    int fd = open(DB_FILEPATH, O_RDONLY);
    database_save_t *db_save;
    bool exit_value;

    create_empty_database(db);
    if (fd < 0)
        return true;
    db_save = read_database_save(fd);
    if (db_save == NULL) {
        printf("read_database_save: %s\n", strerror(errno));
        return false;
    }
    if (close(fd) == -1) {
        printf("load_database => close: %s\n", strerror(errno));
        return false;
    }
    exit_value = convert_saved_db_to_release_db(db_save, db);
    destroy_database_save_t(db_save);
    return exit_value;
}
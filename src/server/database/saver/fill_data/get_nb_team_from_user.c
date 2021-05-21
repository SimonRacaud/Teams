/*
** EPITECH PROJECT, 2021
** get_nb_team_from_user.c
** File description:
** get_nb_team_from_user function
*/

#include "database.h"

size_t get_nb_team_from_user(user_t *user)
{
    size_t nb = 0;
    team_t *user_team = NULL;

    LIST_FOREACH(user_team, &user->teams, entries) {
        nb++;
    }
    return nb;
}
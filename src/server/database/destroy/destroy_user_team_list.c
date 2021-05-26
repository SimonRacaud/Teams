/*
** EPITECH PROJECT, 2021
** destroy
** File description:
** destroy_user_team_list.c - Created: 26/05/2021
*/

#include "database.h"

void destroy_user_team_list(user_t *user_node)
{
    team_ptr_t *team_ptr = NULL;
    team_ptr_t *last_team_ptr = NULL;

    LIST_FOREACH(team_ptr, &user_node->teams, entries)
    {
        free_zero(last_team_ptr, sizeof(team_ptr_t));
        last_team_ptr = team_ptr;
    }
    free_zero(last_team_ptr, sizeof(team_ptr_t));
}

void destroy_team_user_list(team_t *team_node)
{
    user_ptr_t *user_ptr = NULL;
    user_ptr_t *last_user_ptr = NULL;

    LIST_FOREACH(user_ptr, &team_node->users, entries)
    {
        free_zero(last_user_ptr, sizeof(user_ptr_t));
        last_user_ptr = user_ptr;
    }
    free_zero(last_user_ptr, sizeof(user_ptr_t));
}
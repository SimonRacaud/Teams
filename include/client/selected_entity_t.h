/*
** EPITECH PROJECT, 2021
** B-NWP-400-REN-4-1-myteams-simon.racaud
** File description:
** 13/05/2021 selected_entity_t.h
*/

#ifndef SELECTED_ENTITY_T_H
#define SELECTED_ENTITY_T_H

#include "uuid.h"

typedef struct selected_entity_s {
    uuid_t team;
    uuid_t channel;
    uuid_t thread;
} selected_entity_t;

#endif // SELECTED_ENTITY_T_H
